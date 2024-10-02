#include <Arduino_LSM9DS1.h>          // IMU传感器库
#include <Wire.h>                     // I2C通信库
#include <SparkFun_MAX3010x_Sensor.h> // MAX30102传感器库

// 创建MAX30102对象
MAX30105 particleSensor;

// 定义变量存储传感器数据
// IMU数据
float xAcc, yAcc, zAcc;
float xGyro, yGyro, zGyro;

// 心率和血氧数据
long irValue;
float heartRate;
float spo2;

// 初始化函数
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
}

void loop() {
  // 读取IMU数据
  readIMUData();

  // 读取心率和血氧数据
  readHeartRateAndSpO2();

  // 在串口监视器上打印数据，方便调试
  printSensorData();

  delay(100); // 延时100毫秒，控制采样率为10Hz
}

// 读取IMU数据的函数
void readIMUData() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(xAcc, yAcc, zAcc);
  }

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(xGyro, yGyro, zGyro);
  }

  // 对加速度数据进行简单的低通滤波
  xAcc = lowPassFilter(xAcc);
  yAcc = lowPassFilter(yAcc);
  zAcc = lowPassFilter(zAcc);

  // 对陀螺仪数据进行简单的低通滤波
  xGyro = lowPassFilter(xGyro);
  yGyro = lowPassFilter(yGyro);
  zGyro = lowPassFilter(zGyro);
}

// 读取心率和血氧数据的函数
void readHeartRateAndSpO2() {
  irValue = particleSensor.getIR(); // 获取红外值

  if (checkForBeat(irValue)) {
    // 计算心率
    heartRate = particleSensor.getBeatsPerMinute();
    // 计算血氧（这里使用占位值，需要实际算法）
    spo2 = calculateSpO2();
  } else {
    // 未检测到心跳，设置为0或保持上一次值
    heartRate = 0;
    spo2 = 0;
  }
}

// 简单的低通滤波函数
float lowPassFilter(float input) {
  static float output = 0;
  float alpha = 0.5; // 滤波系数，介于0-1之间
  output = alpha * input + (1 - alpha) * output;
  return output;
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
    lastBeat = currentTime;

    beatsPerMinute = 60 / (timeDiff / 1000.0);

    // 平滑心率值
    beatAvg[beatAvgIndex % 4] = (int)beatsPerMinute;
    beatAvgIndex++;

    beatsPerMinute = (beatAvg[0] + beatAvg[1] + beatAvg[2] + beatAvg[3]) / 4.0;

    particleSensor.setBeatsPerMinute(beatsPerMinute);

    return true;
  } else {
    return false;
  }
}

// 血氧计算函数（占位函数，需要实际算法）
float calculateSpO2() {
  // 实际的血氧计算需要复杂的算法和校准
  // 这里简化处理，返回固定值
  return 98.0;
}

// 打印传感器数据的函数
void printSensorData() {
  Serial.print("加速度计数据 (g): X=");
  Serial.print(xAcc);
  Serial.print(", Y=");
  Serial.print(yAcc);
  Serial.print(", Z=");
  Serial.println(zAcc);

  Serial.print("陀螺仪数据 (dps): X=");
  Serial.print(xGyro);
  Serial.print(", Y=");
  Serial.print(yGyro);
  Serial.print(", Z=");
  Serial.println(zGyro);

  Serial.print("心率 (bpm): ");
  Serial.print(heartRate);
  Serial.print(", 血氧 (%): ");
  Serial.println(spo2);

  Serial.println("---------------------------");
}
