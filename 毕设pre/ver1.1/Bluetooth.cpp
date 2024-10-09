#include "Bluetooth.h"

// 定义服务 UUID 和特征 UUID
#define SENSOR_SERVICE_UUID        "19B10000-E8F2-537E-4F6C-D104768A1214"
#define ROLL_CHARACTERISTIC_UUID   "19B10001-E8F2-537E-4F6C-D104768A1214"
#define PITCH_CHARACTERISTIC_UUID  "19B10002-E8F2-537E-4F6C-D104768A1214"
#define HEART_RATE_CHARACTERISTIC_UUID "19B10003-E8F2-537E-4F6C-D104768A1214"
#define SPO2_CHARACTERISTIC_UUID   "19B10004-E8F2-537E-4F6C-D104768A1214"

// 创建 BLE 服务和特征对象
BLEService sensorService(SENSOR_SERVICE_UUID);

// 定义 BLE 特征
BLEFloatCharacteristic rollCharacteristic(ROLL_CHARACTERISTIC_UUID, BLERead | BLENotify);
BLEFloatCharacteristic pitchCharacteristic(PITCH_CHARACTERISTIC_UUID, BLERead | BLENotify);
BLEFloatCharacteristic heartRateCharacteristic(HEART_RATE_CHARACTERISTIC_UUID, BLERead | BLENotify);
BLEFloatCharacteristic spo2Characteristic(SPO2_CHARACTERISTIC_UUID, BLERead | BLENotify);

// BLE 连接状态变量
BLEDevice central;

// 初始化 BLE
void initBLE() {
  if (!BLE.begin()) {
    Serial.println("初始化BLE失败！");
    while (1);
  }
  Serial.println("BLE初始化成功");

  // 设置设备名称和本地名称
  BLE.setDeviceName("Nano33BLE");
  BLE.setLocalName("Nano33BLE");
  BLE.setAdvertisedService(sensorService); // 设置要广播的服务

  // 添加特征到服务
  sensorService.addCharacteristic(rollCharacteristic);
  sensorService.addCharacteristic(pitchCharacteristic);
  sensorService.addCharacteristic(heartRateCharacteristic);
  sensorService.addCharacteristic(spo2Characteristic);

  // 添加服务
  BLE.addService(sensorService);

  // 设置初始值（可选）
  rollCharacteristic.writeValue(0.0);
  pitchCharacteristic.writeValue(0.0);
  heartRateCharacteristic.writeValue(0.0);
  spo2Characteristic.writeValue(0.0);

  // 开始广播
  BLE.advertise();
  Serial.println("开始BLE广播，等待设备连接...");
}

// 更新 BLE 特征值
void updateBLECharacteristics(float roll, float pitch, float heartRate, float spo2) {
  rollCharacteristic.writeValue(roll);
  pitchCharacteristic.writeValue(pitch);
  heartRateCharacteristic.writeValue(heartRate);
  spo2Characteristic.writeValue(spo2);
}

// 轮询 BLE 事件并处理连接
void pollBLE() {
  // 监听 BLE 设备的连接
  BLEDevice newCentral = BLE.central();

  if (newCentral && !central) {
    // 有设备连接
    central = newCentral;
    Serial.print("已连接至设备：");
    Serial.println(central.address());
  }

  if (central && !central.connected()) {
    // 设备已断开连接
    Serial.print("设备已断开连接：");
    Serial.println(central.address());
    central = 0;
  }

  // 处理 BLE 事件
  BLE.poll();
}
