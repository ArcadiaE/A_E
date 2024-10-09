#include "Filter.h"
#include <math.h>  // 数学函数库

// 定义滤波器参数
const float imuFilterAlpha = 0.1;

// 滤波后的数据
float ax_filtered = 0, ay_filtered = 0, az_filtered = 0;
float gx_filtered = 0, gy_filtered = 0, gz_filtered = 0;

// 归一化后的数据
float ax_normalized = 0, ay_normalized = 0, az_normalized = 0;
float gx_normalized = 0, gy_normalized = 0, gz_normalized = 0;
float roll_normalized = 0, pitch_normalized = 0;

// 初始化滤波器
void initFilter() {
  ax_filtered = ay_filtered = az_filtered = 0;
  gx_filtered = gy_filtered = gz_filtered = 0;
}

// 低通滤波器函数
void imuLowPassFilter(float ax, float ay, float az, float gx, float gy, float gz) {
  // 加速度计滤波
  ax_filtered = imuFilterAlpha * ax + (1 - imuFilterAlpha) * ax_filtered;
  ay_filtered = imuFilterAlpha * ay + (1 - imuFilterAlpha) * ay_filtered;
  az_filtered = imuFilterAlpha * az + (1 - imuFilterAlpha) * az_filtered;

  // 陀螺仪滤波
  gx_filtered = imuFilterAlpha * gx + (1 - imuFilterAlpha) * gx_filtered;
  gy_filtered = imuFilterAlpha * gy + (1 - imuFilterAlpha) * gy_filtered;
  gz_filtered = imuFilterAlpha * gz + (1 - imuFilterAlpha) * gz_filtered;
}

// 数据归一化函数
void normalizeIMUData(float roll, float pitch) {
  // 假设加速度计范围是 -4g 到 +4g，陀螺仪范围是 -2000 dps 到 +2000 dps
  ax_normalized = (ax_filtered + 4.0) / 8.0;
  ay_normalized = (ay_filtered + 4.0) / 8.0;
  az_normalized = (az_filtered + 4.0) / 8.0;

  gx_normalized = (gx_filtered + 2000.0) / 4000.0;
  gy_normalized = (gy_filtered + 2000.0) / 4000.0;
  gz_normalized = (gz_filtered + 2000.0) / 4000.0;

  // 姿态角度归一化
  roll_normalized = (roll + 180.0) / 360.0;
  pitch_normalized = (pitch + 180.0) / 360.0;
}

// 计算数组平均值的函数
float calculateAverage(float *buffer, int size) {
  float sum = 0;
  for (int i = 0; i < size; i++) {
    sum += buffer[i];
  }
  return sum / size;
}

// 检查IMU数据是否有效
bool isValidIMUData(float ax, float ay, float az, float gx, float gy, float gz) {
  // 设置合理的物理范围阈值
  if (abs(ax) > 16.0 || abs(ay) > 16.0 || abs(az) > 16.0) {
    return false;
  }
  if (abs(gx) > 2000.0 || abs(gy) > 2000.0 || abs(gz) > 2000.0) {
    return false;
  }
  return true;
}
