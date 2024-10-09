#include <Arduino_LSM9DS1.h>          // IMU传感器库
#include <Wire.h>                     // I2C通信库
#include <SparkFun_MAX3010x_Sensor.h> // MAX30102传感器库
#include <ArduinoBLE.h>               // BLE库

// 创建MAX30102对象
MAX30105 particleSensor;

// 定义BLE服务和特征
BLEService sensorService("180D"); // 心率服务UUID（标准心率服务）
BLECharacteristic imuCharacteristic("2A37", BLERead | BLENotify, 24);   // IMU数据特征
BLECharacteristic hrCharacteristic("2A37", BLERead | BLENotify, 2);     // 心率数据特征
BLECharacteristic spo2Characteristic("2A5F", BLERead | BLENotify, 2);   // 血氧数据特征

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // 初始化IMU传感器
  if (!IMU.begin()) {
    Serial.println("无法初始化IMU!");
    while (1);
  }
  Serial.println("IMU初始化成功");

  // 初始化MAX30102传感器
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("无法找到MAX30102传感器");
    while (1);
  }
  Serial.println("MAX30102初始化成功");

  // 设置MAX30102传感器参数
  particleSensor.setup(); // 使用默认设置
  particleSensor.setPulseAmplitudeRed(0x0A); // 设置红光LED强度（根据需要调整）
  particleSensor.setPulseAmplitudeGreen(0);  // 关闭绿光LED

  // 初始化BLE
  if (!BLE.begin()) {
    Serial.println("无法初始化BLE模块");
    while (1);
  }
  Serial.println("BLE初始化成功");

  // 设置BLE设备信息
  BLE.setLocalName("BadmintonTracker");
  BLE.setAdvertisedService(sensorService);

  // 添加特征到服务
  sensorService.addCharacteristic(imuCharacteristic);
  sensorService.addCharacteristic(hrCharacteristic);
  sensorService.addCharacteristic(spo2Characteristic);

  // 添加服务
  BLE.addService(sensorService);

  // 开始广播
  BLE.advertise();
  Serial.println("开始广播BLE服务");
}

void loop() {
  // 监听BLE连接
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("已连接到中央设备: ");
    Serial.println(central.address());

    while (central.connected()) {
      // 读取IMU数据
      float xAcc, yAcc, zAcc;
      float xGyro, yGyro, zGyro;

      if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(xAcc, yAcc, zAcc);
      }

      if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(xGyro, yGyro, zGyro);
      }

      // 将IMU数据转换为字节数组
      uint8_t imuData[24];
      memcpy(imuData, &xAcc, 4);
      memcpy(imuData + 4, &yAcc, 4);
      memcpy(imuData + 8, &zAcc, 4);
      memcpy(imuData + 12, &xGyro, 4);
      memcpy(imuData + 16, &yGyro, 4);
      memcpy(imuData + 20, &zGyro, 4);

      // 更新IMU特征值
      imuCharacteristic.writeValue(imuData, 24);

      // 读取心率和血氧数据
      long irValue = particleSensor.getIR();

      if (checkForBeat(irValue)) {
        // 计算心率
        float heartRate = particleSensor.getBeatsPerMinute();
        uint8_t hrData = (uint8_t)heartRate;
        hrCharacteristic.writeValue(&hrData, 1);

        // 获取血氧水平（简单处理，实际需要复杂算法）
        float spo2 = calculateSpO2();
        uint8_t spo2Data = (uint8_t)spo2;
        spo2Characteristic.writeValue(&spo2Data, 1);

        Serial.print("心率: ");
        Serial.print(heartRate);
        Serial.print(" bpm, 血氧: ");
        Serial.print(spo2);
        Serial.println(" %");
      }

      delay(40); // 延时以控制采样率，25Hz左右
    }

    Serial.print("中央设备已断开连接: ");
    Serial.println(central.address());
  }
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
    srand(time(0));  
    return 97 + rand() % 4;
}
