#!/usr/bin/python3

import dbus


def main():
    # 连接到 dbus 的 system bus
    bus = dbus.SystemBus()
    # 获取 /org/freedesktop/hostname1 代理的对象 org.freedesktop.hostname1，这个对象是 systemd-hostname 服务注册到 dbus 的
    obj_name = "org.freedesktop.hostname1"
    obj = bus.get_object(obj_name, '/org/freedesktop/hostname1')
    # 获取 Properties 接口
    interface = dbus.Interface(obj, 'org.freedesktop.DBus.Properties')
    print(interface.GetAll(obj_name))
    # 获取 hostname
    hostname = interface.Get(obj_name, 'Hostname')
    print("=========================================")
    print(hostname)
    pass


if __name__ == "__main__":
    main()
