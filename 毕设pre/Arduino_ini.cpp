#include <Arduino_LSM9DS1.h>          // IMU传感器库
#include <Wire.h>                     // I2C通信库
#include <SparkFun_MAX3010x_Sensor.h> // MAX30102传感器库
#include <ArduinoBLE.h>               // BLE通信库

// 创建MAX30102对象
MAX30105 particleSensor;

// 定义BLE服务和特征UUID
BLEService sensorService("180A"); // 自定义服务UUID

// 定义BLE特征
BLECharacteristic imuCharacteristic("2A5A", BLENotify, sizeof(float) * 6); // IMU数据特征
BLECharacteristic hrCharacteristic("2A37", BLENotify, sizeof(float));      // 心率数据特征
BLECharacteristic spo2Characteristic("2A5F", BLENotify, sizeof(float));    // 血氧数据特征

// 定义变量存储传感器数据
// IMU原始数据
float ax, ay, az; // 加速度计数据
float gx, gy, gz; // 陀螺仪数据

// 姿态角度（滚转、俯仰）
float roll, pitch;

// 互补滤波器参数
float dt = 0.01; // 时间间隔，单位：秒
float alpha = 0.98; // 互补滤波器系数

// 心率和血氧数据
long irValue;
float heartRate = 0;
float spo2 = 0;

// 心率和血氧的移动平均滤波器
#define HR_FILTER_SIZE 5
float hrBuffer[HR_FILTER_SIZE];
int hrIndex = 0;

#define SPO2_FILTER_SIZE 5
float spo2Buffer[SPO2_FILTER_SIZE];
int spo2Index = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // 初始化IMU传感器
  if (!IMU.begin()) {
    Serial.println("无法初始化IMU传感器！");
    while (1);
  }
  Serial.println("IMU传感器初始化成功");

  // 初始化MAX30102传感器
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("无法找到MAX30102传感器！");
    while (1);
  }
  Serial.println("MAX30102传感器初始化成功");

  // 设置MAX30102传感器参数
  particleSensor.setup(); // 使用默认配置
  particleSensor.setPulseAmplitudeRed(0x0A); // 调整红光LED强度
  particleSensor.setPulseAmplitudeIR(0x0A);  // 调整红外LED强度

  // 初始化滤波器缓冲区
  for (int i = 0; i < HR_FILTER_SIZE; i++) {
    hrBuffer[i] = 0;
  }
  for (int i = 0; i < SPO2_FILTER_SIZE; i++) {
    spo2Buffer[i] = 0;
  }

  // 初始化BLE模块
  if (!BLE.begin()) {
    Serial.println("无法初始化BLE模块！");
    while (1);
  }
  Serial.println("BLE模块初始化成功");

  // 设置BLE设备名称和服务
  BLE.setLocalName("BadmintonTracker");
  BLE.setAdvertisedService(sensorService);

  // 添加特征到服务
  sensorService.addCharacteristic(imuCharacteristic);
  sensorService.addCharacteristic(hrCharacteristic);
  sensorService.addCharacteristic(spo2Characteristic);

  // 添加服务到BLE
  BLE.addService(sensorService);

  // 开始广播
  BLE.advertise();
  Serial.println("开始广播BLE服务");
}

void loop() {
  // 等待并检测中央设备连接
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("已连接到中央设备: ");
    Serial.println(central.address());

    while (central.connected()) {
      // 读取和处理传感器数据
      readAndFuseIMUData();
      readAndFilterHeartRateAndSpO2();

      // 将IMU数据打包成数组
      float imuData[6] = {ax, ay, az, gx, gy, gz};

      // 将数据写入BLE特征
      imuCharacteristic.writeValue((uint8_t*)imuData, sizeof(imuData));
      hrCharacteristic.writeValue(heartRate);
      spo2Characteristic.writeValue(spo2);

      // （可选）在串口监视器上打印数据
      printSensorData();

      delay(dt * 1000); // 控制循环频率，与dt对应
    }

    Serial.print("中央设备已断开连接: ");
    Serial.println(central.address());
  }
}

// 读取IMU数据并进行数据融合的函数
void readAndFuseIMUData() {
  // 读取加速度计数据
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }

  // 读取陀螺仪数据
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);
  }

  // 计算姿态角度
  // 使用加速度计计算俯仰角和滚转角
  float rollAcc = atan2(ay, az) * 180 / PI;
  float pitchAcc = atan(-ax / sqrt(ay * ay + az * az)) * 180 / PI;

  // 使用陀螺仪数据更新角度
  static float lastRoll = 0;
  static float lastPitch = 0;

  // 互补滤波器融合
  roll = alpha * (lastRoll + gx * dt) + (1 - alpha) * rollAcc;
  pitch = alpha * (lastPitch + gy * dt) + (1 - alpha) * pitchAcc;

  lastRoll = roll;
  lastPitch = pitch;
}

// 读取心率和血氧数据并进行滤波的函数
void readAndFilterHeartRateAndSpO2() {
  irValue = particleSensor.getIR(); // 获取红外值

  if (checkForBeat(irValue)) {
    // 计算心率
    float rawHeartRate = particleSensor.getBeatsPerMinute();
    // 移动平均滤波
    hrBuffer[hrIndex % HR_FILTER_SIZE] = rawHeartRate;
    hrIndex++;
    heartRate = calculateAverage(hrBuffer, HR_FILTER_SIZE);

    // 计算血氧（这里使用占位值，需要实际算法）
    float rawSpO2 = calculateSpO2();
    // 移动平均滤波
    spo2Buffer[spo2Index % SPO2_FILTER_SIZE] = rawSpO2;
    spo2Index++;
    spo2 = calculateAverage(spo2Buffer, SPO2_FILTER_SIZE);
  } else {
    // 未检测到心跳，保持上一次的值
    // 可以选择在一段时间内未检测到心跳时，将心率和血氧值设为0
  }
}

// 计算数组平均值的函数
float calculateAverage(float *buffer, int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += buffer[i];
  }
  return sum / size;
}

// 心率检测函数
bool checkForBeat(long irValue) {
  static uint32_t lastBeat = 0;
  static float beatsPerMinute;
  static int beatAvg[4];
  static int beatAvgIndex = 0;

  // 检测心跳的算法实现（简化版）
  if (irValue > 50000) { // 根据环境调整阈值
    uint32_t currentTime = millis();
    uint32_t timeDiff = currentTime - lastBeat;

    if (timeDiff > 250) { // 限制最大心率240 bpm
      lastBeat = currentTime;

      beatsPerMinute = 60 / (timeDiff / 1000.0);

      // 平滑心率值
      beatAvg[beatAvgIndex % 4] = (int)beatsPerMinute;
      beatAvgIndex++;

      beatsPerMinute = (beatAvg[0] + beatAvg[1] + beatAvg[2] + beatAvg[3]) / 4.0;

      particleSensor.setBeatsPerMinute(beatsPerMinute);

      return true;
    }
  }
  return false;
}

// 血氧计算函数（占位函数，需要实际算法）
float calculateSpO2() {
  // 实际的血氧计算需要复杂的算法和校准
  // 这里简化处理，返回固定值
  return 98.0;
}

// 打印传感器数据的函数
void printSensorData() {
  Serial.print("姿态角度 (deg): Roll=");
  Serial.print(roll);
  Serial.print(", Pitch=");
  Serial.println(pitch);

  Serial.print("心率 (bpm): ");
  Serial.print(heartRate);
  Serial.print(", 血氧 (%): ");
  Serial.println(spo2);

  Serial.println("---------------------------");
}
