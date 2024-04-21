#!/usr/bin/python3

"""
扫描并报告设备的详细信息

"""

import json

from gi.repository import GLib

import bluetooth_utils
import bluetooth_constants
import dbus
import dbus.mainloop.glib
import sys

adapter_interface = None
mainloop = None
timer_id = None

devices = {}
managed_objects_found = 0


def main():
    # 扫描超时时间（秒）
    scantime = 60 * 1000

    # 初始化 dbus
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()

    # 获取已配对的蓝牙设备
    print("列出 BlueZ 已知的设备：")
    get_known_devices(bus)
    print("找到", managed_objects_found, "个已配对的设备")
    print("正在进行扫描")
    discover_devices(bus, scantime)


def get_known_devices(bus):
    global managed_objects_found
    object_manager = dbus.Interface(bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, "/"), bluetooth_constants.DBUS_OM_IFACE)
    managed_objects = object_manager.GetManagedObjects()

    for path, ifaces in managed_objects.items():
        if "org.bluez.Adapter1" in ifaces:
            adapter = ifaces["org.bluez.Adapter1"]
            print("蓝牙适配器的详细信息：")
            print("Address:", adapter["Address"])
            print("Name:", adapter["Name"])

        for iface_name in ifaces:
            if iface_name == bluetooth_constants.DEVICE_INTERFACE:
                managed_objects_found += 1
                print("EXI path  : ", path)
                device_properties = ifaces[bluetooth_constants.DEVICE_INTERFACE]
                devices[path] = device_properties
                if 'Address' in device_properties:
                    print("EXI bdaddr: ", bluetooth_utils.dbus_to_python(device_properties['Address']))
                if 'Connected' in device_properties:
                    print("EXI cncted: ", bluetooth_utils.dbus_to_python(device_properties['Connected']))
                print("------------------------------")


def discover_devices(bus, timeout):
    global adapter_interface
    global mainloop
    global timer_id
    adapter_path = bluetooth_constants.BLUEZ_NAMESPACE + bluetooth_constants.ADAPTER_NAME

    # 获取适配器接口，以便我们可以调用它的方法
    adapter_object = bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, adapter_path)
    adapter_interface = dbus.Interface(adapter_object, bluetooth_constants.ADAPTER_INTERFACE)

    # 注册信号处理函数，以便我们可以异步报告发现的设备

    # 当 BlueZ 收到来自其未知设备的广告数据包时，会发出 InterfacesAdded 信号
    bus.add_signal_receiver(
        interfaces_added,
        dbus_interface=bluetooth_constants.DBUS_OM_IFACE,
        signal_name="InterfacesAdded"
    )

    # 当设备“消失”时，BlueZ 会发出 InterfacesRemoved 信号
    bus.add_signal_receiver(
        interfaces_removed,
        dbus_interface=bluetooth_constants.DBUS_OM_IFACE,
        signal_name="InterfacesRemoved"
    )

    # 当设备发生变化时，BlueZ 会发出 PropertiesChanged 信号。 RSSI 值
    bus.add_signal_receiver(
        properties_changed,
        dbus_interface=bluetooth_constants.DBUS_PROPERTIES,
        signal_name="PropertiesChanged",
        path_keyword="path"
    )

    mainloop = GLib.MainLoop()
    timer_id = GLib.timeout_add(timeout, discovery_timeout)
    adapter_interface.StartDiscovery(byte_arrays=True)

    mainloop.run()

    device_list = devices.values()
    discovered_devices = []
    for _ in device_list:
        dev = {}
        discovered_devices.append(dev)

    return discovered_devices


def interfaces_added(path, interfaces):
    # interfaces 是字典条目的数组
    if not bluetooth_constants.DEVICE_INTERFACE in interfaces:
        return
    device_properties = interfaces[bluetooth_constants.DEVICE_INTERFACE]
    if path not in devices:
        print("NEW path  :", path)
        devices[path] = device_properties
        dev = devices[path]
        if 'Address' in dev:
            print("NEW bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
        if 'Name' in dev:
            print("NEW name  : ", bluetooth_utils.dbus_to_python(dev['Name']))
        if 'RSSI' in dev:
            print("NEW RSSI  : ", bluetooth_utils.dbus_to_python(dev['RSSI']))
        print("------------------------------")


def interfaces_removed(path, interfaces):
    # interfaces 是该信号中字典字符串数组
    if not bluetooth_constants.DEVICE_INTERFACE in interfaces:
        return
    if path in devices:
        dev = devices[path]
        if 'Address' in dev:
            print("DEL bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
        else:
            print("DEL path  : ", path)
            print("------------------------------")
        del devices[path]


def properties_changed(interface, changed, _, path):
    if interface != bluetooth_constants.DEVICE_INTERFACE:
        return
    if path in devices:
        devices[path] = dict(devices[path].items())
        devices[path].update(changed.items())
    else:
        devices[path] = changed

    dev = devices[path]
    print("CHG path  :", path)
    if 'Address' in dev:
        print("CHG bdaddr: ", bluetooth_utils.dbus_to_python(dev['Address']))
    if 'Name' in dev:
        print("CHG name  : ", bluetooth_utils.dbus_to_python(dev['Name']))
    if 'RSSI' in dev:
        print("CHG RSSI  : ", bluetooth_utils.dbus_to_python(dev['RSSI']))
    print("------------------------------")


def discovery_timeout():
    global adapter_interface
    global mainloop
    global timer_id
    GLib.source_remove(timer_id)
    mainloop.quit()
    adapter_interface.StopDiscovery()
    bus = dbus.SystemBus()
    bus.remove_signal_receiver(interfaces_added, "InterfacesAdded")
    bus.remove_signal_receiver(interfaces_added, "InterfacesRemoved")
    bus.remove_signal_receiver(properties_changed, "PropertiesChanged")
    list_devices_found()
    return True


def list_devices_found():
    print("Full list of devices", len(devices), "discovered:")
    print("------------------------------")
    for path in devices:
        dev = devices[path]
        print(bluetooth_utils.dbus_to_python(dev['Address']))


if __name__ == "__main__":
    main()
