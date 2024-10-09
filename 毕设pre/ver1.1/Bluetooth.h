#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <ArduinoBLE.h> // 引入 ArduinoBLE 库

// 函数声明
void initBLE();
void updateBLECharacteristics(float roll, float pitch, float heartRate, float spo2);
void pollBLE();

// 在其他文件中需要访问的变量和对象
extern BLEService sensorService;

// 定义 BLE 特征
extern BLEFloatCharacteristic rollCharacteristic;
extern BLEFloatCharacteristic pitchCharacteristic;
extern BLEFloatCharacteristic heartRateCharacteristic;
extern BLEFloatCharacteristic spo2Characteristic;

// BLE 连接状态变量
extern BLEDevice central;

#endif
