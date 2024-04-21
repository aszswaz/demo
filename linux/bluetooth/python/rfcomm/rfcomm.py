#!/bin/python3

import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib


class RFCommProfile(dbus.service.Object):
    def __init__(self, bus):
        self.path = "/org/bluez/ldsg/advertisement01"
        self.bus = bus

    @dbus.service.method("org.bluez.Profile1")
    def Release(self):
        print("RFCommProfile register success.")
        pass

    @dbus.service.method(
        "org.bluez.Profile1",
        in_signature="ooa{sq}"
    )
    def NewConnection(self, device, fd, fd_properties):
        print("NewConnection")
        pass


def main():
    uuid = "26f238ae-fd9e-11ee-b718-2bb40603ed66"

    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()

    manager = dbus.Interface(
        bus.get_object("org.bluez", "/org/bluez/hci0"),
        "org.bluez.ProfileManager1"
    )
    profile = RFCommProfile(bus)
    opt = dbus.Dictionary(mapping_or_iterable={
        dbus.String("Name"): dbus.String("Hello World"),
        dbus.String("Role"): dbus.String("server"),
        dbus.String("Channel"): dbus.UInt16(28),
        dbus.String("RequireAuthentication"): dbus.Boolean(False),
        dbus.String("RequireAuthorization"): dbus.Boolean(False)
    }, signature="a{sv}")
    manager.RegisterProfile(profile.path, uuid, opt,
        reply_handler=register_ad_cb,
        error_handler=register_ad_error_cb
    )

    mainloop = GLib.MainLoop()
    mainloop.run()
    pass


def register_ad_cb():
    print('Advertisement registered OK')


def register_ad_error_cb(error):
    print('Error: Failed to register advertisement: ' + str(error))
    quiet()


main()
