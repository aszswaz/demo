#!/usr/bin/python3

from dbus import mainloop
import bluetooth_constants
import bluetooth_exceptions
import dbus
import dbus.exceptions
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

"""
启动蓝牙广播，使 center 设备可以发现本机
"""

bus = None
adapter_path = None
adv_mgr_interface = None
mainloop = None
adv = None


class Advertisement(dbus.service.Object):
    PATH_BASE = '/org/bluez/ldsg/advertisement'

    def __init__(self, bus, index, advertising_type):
        self.path = self.PATH_BASE + str(index)
        self.bus = bus
        self.ad_type = advertising_type
        self.service_uuids = None
        self.manufacturer_data = None
        self.solicit_uuids = None
        self.service_data = None
        self.local_name = "Hello World"
        self.include_tx_power = False
        self.data = None
        self.discoverable = True
        dbus.service.Object.__init__(self, bus, self.path)

    def get_properties(self):
        properties = dict()
        properties['Type'] = self.ad_type
        if self.service_uuids is not None:
            properties['ServiceUUIDs'] = dbus.Array(
                self.service_uuids,
                signature='s'
            )
        if self.solicit_uuids is not None:
            properties['SolicitUUIDs'] = dbus.Array(
                self.solicit_uuids,
                signature='s'
            )
        if self.manufacturer_data is not None:
            properties['ManufacturerData'] = dbus.Dictionary(
                self.manufacturer_data, signature='qv'
            )
        if self.service_data is not None:
            properties['ServiceData'] = dbus.Dictionary(
                self.service_data,
                signature='sv'
            )
        if self.local_name is not None:
            properties['LocalName'] = dbus.String(self.local_name)
        if self.discoverable is not None and self.discoverable == True:
            properties['Discoverable'] = dbus.Boolean(self.discoverable)
        if self.include_tx_power:
            properties['Includes'] = dbus.Array(["tx-power"], signature='s')

        if self.data is not None:
            properties['Data'] = dbus.Dictionary(
                self.data, signature='yv'
            )
        return {bluetooth_constants.ADVERTISING_MANAGER_INTERFACE: properties}

    def get_path(self):
        return dbus.ObjectPath(self.path)

    @dbus.service.method(
        bluetooth_constants.DBUS_PROPERTIES,
        in_signature='s',
        out_signature='a{sv}'
    )
    def GetAll(self, interface):
        if interface != bluetooth_constants.ADVERTISEMENT_INTERFACE:
            raise bluetooth_exceptions.InvalidArgsException()
        return self.get_properties()[bluetooth_constants.ADVERTISING_MANAGER_INTERFACE]

    @dbus.service.method(
        bluetooth_constants.ADVERTISING_MANAGER_INTERFACE,
        in_signature='',
        out_signature=''
    )
    def Release(self):
        print('%s: Released' % self.path)


def main():
    global mainloop, adv, adv_mgr_interface

    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()
    # 适配器地址
    adapter_path = bluetooth_constants.BLUEZ_NAMESPACE + bluetooth_constants.ADAPTER_NAME
    print(adapter_path)

    adv_mgr_interface = dbus.Interface(
        bus.get_object(bluetooth_constants.BLUEZ_SERVICE_NAME, adapter_path),
        bluetooth_constants.ADVERTISING_MANAGER_INTERFACE
    )
    # 我们只注册一个广告对象，因此索引被硬编码为 0
    adv = Advertisement(bus, 0, 'peripheral')
    start_advertising()

    print("Advertising as", adv.local_name)

    mainloop = GLib.MainLoop()
    mainloop.run()


def register_ad_cb():
    print('Advertisement registered OK')


def register_ad_error_cb(error):
    print('Error: Failed to register advertisement: ' + str(error))
    mainloop.quit()


def start_advertising():
    global adv
    global adv_mgr_interface
    print("Registering advertisement", adv.get_path())
    # 注册广播对象，bluez 将会开始广播
    adv_mgr_interface.RegisterAdvertisement(
        adv.get_path(), {},
        reply_handler=register_ad_cb,
        error_handler=register_ad_error_cb
    )


if __name__ == "__main__":
    main()