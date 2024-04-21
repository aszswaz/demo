# 简介

通过蓝牙的 RFCOMM 协议建立可靠 socket 连接

# 执行示例之前

```bash
# 安装 pybluez：https://github.com/pybluez/pybluez
$ sudo apt install python3-bluez
# 让 bluetoothd 兼容旧的命令行工具，比如 sdptool
$ sudo nano /etc/systemd/system/dbus-org.bluez.service
...
ExecStart=/usr/libexec/bluetooth/bluetoothd -C
...
$ sudo sdp add SP
```

# 启动程序

```bash
$ sudo ./rfcomm-service.py
```
