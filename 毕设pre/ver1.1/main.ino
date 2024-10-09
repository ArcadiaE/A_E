#include <Arduino_LSM9DS1.h>  // IMU传感器库（Arduino Nano 33 BLE 自带）
#include <Wire.h>             // I2C通信库
#include "Filter.h"           // 包含滤波器头文件
#include "Bluetooth.h"        // 包含蓝牙模块头文件

// 引入 MAX30102 传感器库
#include "MAX30105.h"
#include "heartRate.h"

// 创建 MAX30105 对象
MAX30105 particleSensor;

// 定义变量存储传感器数据
// IMU原始数据
float ax, ay, az; // 加速度计数据
float gx, gy, gz; // 陀螺仪数据

// 姿态角度（滚转、俯仰）
float roll, pitch;

// 互补滤波器参数
float dt = 0.01;    // 时间间隔，单位：秒
float alpha = 0.98; // 互补滤波器系数

// 心率和血氧数据
long irValue, redValue;
float heartRate = 0;
float spo2 = 0;

// 滤波器缓冲区大小
#define HR_FILTER_SIZE 5
float hrBuffer[HR_FILTER_SIZE];
int hrIndex = 0;
#define SPO2_FILTER_SIZE 5
float spo2Buffer[SPO2_FILTER_SIZE];
int spo2Index = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // 初始化IMU传感器（板载）
  if (!IMU.begin()) {
    Serial.println("无法初始化板载IMU传感器！");
    while (1);
  }
  Serial.println("IMU传感器初始化成功");

  // 初始化滤波器
  initFilter();

  // 初始化MAX30102传感器
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("无法找到MAX30102传感器！");
    while (1);
  }
  Serial.println("MAX30102传感器初始化成功");

  // 设置MAX30102传感器参数
  byte ledBrightness = 60; // LED亮度，0-255
  byte sampleAverage = 4;  // 采样平均次数
  byte ledMode = 2;        // LED模式，2 = 红外和红光
  int sampleRate = 100;    // 采样率
  int pulseWidth = 411;    // 脉冲宽度
  int adcRange = 16384;    // ADC范围

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

  // 初始化滤波器缓冲区
  for (int i = 0; i < HR_FILTER_SIZE; i++) {
    hrBuffer[i] = 0;
  }
  for (int i = 0; i < SPO2_FILTER_SIZE; i++) {
    spo2Buffer[i] = 0;
  }

  // 初始化蓝牙
  initBLE();
}

void loop() {
  // 处理 BLE 事件和连接
  pollBLE();

  // 如果有设备连接，更新特征值
  if (central && central.connected()) {
    // 读取IMU数据并进行数据融合
    readAndFuseIMUData();

    // 读取心率和血氧数据并进行滤波
    readAndFilterHeartRateAndSpO2();

    // 更新 BLE 特征值
    updateBLECharacteristics(roll_normalized, pitch_normalized, heartRate, spo2);

    // 可选：在串口监视器上打印数据，方便调试
    printSensorData();
  }

  delay(dt * 1000); // 控制循环频率，与dt对应
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

  // 将加速度单位从 g 转换为 m/s^2（可选）
  // ax *= 9.80665;
  // ay *= 9.80665;
  // az *= 9.80665;

  // 将陀螺仪单位从 dps 转换为 rad/s（可选）
  // gx *= PI / 180;
  // gy *= PI / 180;
  // gz *= PI / 180;

  // 检查数据是否有效
  if (!isValidIMUData(ax, ay, az, gx, gy, gz)) {
    Serial.println("IMU数据异常，跳过本次计算");
    return;
  }

  // 进行低通滤波
  imuLowPassFilter(ax, ay, az, gx, gy, gz);

  // 计算姿态角度
  float rollAcc = atan2(ay_filtered, az_filtered) * 180 / PI;
  float pitchAcc = atan(-ax_filtered / sqrt(ay_filtered * ay_filtered + az_filtered * az_filtered)) * 180 / PI;

  // 使用陀螺仪数据更新角度
  static float rollGyro = 0;
  static float pitchGyro = 0;

  rollGyro += gx_filtered * dt;
  pitchGyro += gy_filtered * dt;

  // 互补滤波器融合
  roll = alpha * (roll + gx_filtered * dt) + (1 - alpha) * rollAcc;
  pitch = alpha * (pitch + gy_filtered * dt) + (1 - alpha) * pitchAcc;

  // 归一化数据
  normalizeIMUData(roll, pitch);
}

// 读取心率和血氧数据并进行滤波的函数
void readAndFilterHeartRateAndSpO2() {
  // 检查是否有新数据可用
  while (particleSensor.available()) {
    redValue = particleSensor.getRed();
    irValue = particleSensor.getIR();

    // 移动到下一个样本
    particleSensor.nextSample();

    // 计算心率和血氧
    float hr = 0, spo2_calc = 0;
    bool result = calculateHeartRateAndSpO2(irValue, redValue, &hr, &spo2_calc);

    if (result) {
      // 移动平均滤波
      hrBuffer[hrIndex % HR_FILTER_SIZE] = hr;
      hrIndex++;
      heartRate = calculateAverage(hrBuffer, HR_FILTER_SIZE);

      spo2Buffer[spo2Index % SPO2_FILTER_SIZE] = spo2_calc;
      spo2Index++;
      spo2 = calculateAverage(spo2Buffer, SPO2_FILTER_SIZE);
    }
  }
}

// 计算心率和血氧的函数
bool calculateHeartRateAndSpO2(long irValue, long redValue, float *hr, float *spo2_calc) {
  // 使用库中的算法计算心率和血氧
  static uint32_t lastBeat = 0;
  static float beatsPerMinute;
  static int beatAvg = 0;

  // 检查心跳
  if (checkForBeat(irValue)) {
    uint32_t delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    // 计算平均心率
    static float bpmSum = 0;
    static int bpmCount = 0;

    bpmSum += beatsPerMinute;
    bpmCount++;

    beatAvg = bpmSum / bpmCount;

    *hr = beatAvg;

    // 血氧计算（需要实际算法）
    // 这里调用库函数或实现您的算法
    *spo2_calc = 98.0; // 占位值
    return true;
  } else {
    return false;
  }
}

// 心率检测函数
bool checkForBeat(long irValue) {
  // 使用库提供的心跳检测算法
  return particleSensor.checkForBeat(irValue);
}

// 打印传感器数据的函数
void printSensorData() {
  Serial.print("姿态角度 (归一化): Roll=");
  Serial.print(roll_normalized, 4);
  Serial.print(", Pitch=");
  Serial.println(pitch_normalized, 4);

  Serial.print("心率 (bpm): ");
  Serial.print(heartRate, 2);
  Serial.print(", 血氧 (%): ");
  Serial.println(spo2, 2);

  Serial.println("---------------------------");
}
