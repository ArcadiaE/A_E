#ifndef FILTER_H
#define FILTER_H

// 定义滤波器参数
extern const float imuFilterAlpha;

// 函数声明
void initFilter();
void imuLowPassFilter(float ax, float ay, float az, float gx, float gy, float gz);
void normalizeIMUData(float roll, float pitch);
float calculateAverage(float *buffer, int size);
bool isValidIMUData(float ax, float ay, float az, float gx, float gy, float gz);

// 全局变量声明
extern float ax_filtered, ay_filtered, az_filtered;
extern float gx_filtered, gy_filtered, gz_filtered;
extern float ax_normalized, ay_normalized, az_normalized;
extern float gx_normalized, gy_normalized, gz_normalized;
extern float roll_normalized, pitch_normalized;

#endif
