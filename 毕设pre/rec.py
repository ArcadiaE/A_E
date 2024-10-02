import asyncio
from bleak import BleakClient, BleakScanner

# 定义设备名称和特征UUID
DEVICE_NAME = "BadmintonTracker"

# 服务和特征UUID（与Arduino代码一致）
SERVICE_UUID = "180A"
IMU_CHAR_UUID = "2A5A"
HR_CHAR_UUID = "2A37"
SPO2_CHAR_UUID = "2A5F"

# 定义处理收到的数据的回调函数
def imu_data_handler(sender, data):
    # 解析IMU数据，假设发送的是6个float数据，共24字节
    import struct
    imu_values = struct.unpack('6f', data)
    ax, ay, az, gx, gy, gz = imu_values
    print(f"IMU数据 - 加速度计: ax={ax:.2f}, ay={ay:.2f}, az={az:.2f}; 陀螺仪: gx={gx:.2f}, gy={gy:.2f}, gz={gz:.2f}")

def hr_data_handler(sender, data):
    # 解析心率数据，假设发送的是一个float数据，4字节
    import struct
    heart_rate = struct.unpack('f', data)[0]
    print(f"心率: {heart_rate:.2f} bpm")

def spo2_data_handler(sender, data):
    # 解析血氧数据，假设发送的是一个float数据，4字节
    import struct
    spo2 = struct.unpack('f', data)[0]
    print(f"血氧: {spo2:.2f} %")

async def run():
    # 扫描附近的BLE设备
    devices = await BleakScanner.discover()
    target_device = None
    for d in devices:
        if d.name == DEVICE_NAME:
            target_device = d
            break

    if not target_device:
        print(f"未找到设备 {DEVICE_NAME}")
        return

    print(f"找到设备 {DEVICE_NAME}: {target_device.address}")

    async with BleakClient(target_device.address) as client:
        # 检查设备是否连接
        if not client.is_connected:
            print("无法连接到设备")
            return

        print("已连接到设备")

        # 订阅IMU特征
        await client.start_notify(IMU_CHAR_UUID, imu_data_handler)

        # 订阅心率特征
        await client.start_notify(HR_CHAR_UUID, hr_data_handler)

        # 订阅血氧特征
        await client.start_notify(SPO2_CHAR_UUID, spo2_data_handler)

        print("开始接收数据... 按 Ctrl+C 停止")

        try:
            # 保持连接，持续接收数据
            while True:
                await asyncio.sleep(1)
        except KeyboardInterrupt:
            print("停止接收数据")

        # 停止通知
        await client.stop_notify(IMU_CHAR_UUID)
        await client.stop_notify(HR_CHAR_UUID)
        await client.stop_notify(SPO2_CHAR_UUID)

if __name__ == "__main__":
    asyncio.run(run())
