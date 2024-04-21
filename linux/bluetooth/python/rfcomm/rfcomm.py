#!/bin/python3

import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib


class RFCommProfile(dbus.service.Object):
    def __init__(self, bus):
        self.path = "/org/bluez/ldsg/profile01"
        self.bus = bus
        dbus.service.Object.__init__(self, bus, self.path)

    @dbus.service.method("org.bluez.Profile1")
    def Release(self):
        print("RFCommProfile register success.")
        pass

    @dbus.service.method(
        "org.bluez.Profile1",
        in_signature="oxa{sq}"
    )
    def NewConnection(self, device, fd, fd_properties):
        print("NewConnection")
        pass


def main():
    uuid = "26f238ae-fd9e-11ee-b718-2bb40603ed66"

    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()

    """
    manager = dbus.Interface(
        bus.get_object("org.bluez", "/org/bluez/hci0"),
        "org.bluez.ProfileManager1"
    )
    """
    manager = dbus.Interface(
        bus.get_object("org.bluez", "/org/bluez"),
        "org.bluez.ProfileManager1"
    )
    profile = RFCommProfile(bus)
    opt = dbus.Dictionary({
        "Name": dbus.String("Hello World"),
        "Service": dbus.String(uuid),
        "Role": dbus.String("server"),
        "Channel": dbus.UInt16(28),
        "RequireAuthentication": dbus.Boolean(False),
        "RequireAuthorization": dbus.Boolean(False)
    }, signature="sv")
    manager.RegisterProfile(
        dbus.ObjectPath(profile.path), 
        dbus.String(uuid), 
        opt,
        reply_handler=register_ad_cb,
        error_handler=register_ad_error_cb
    )

    mainloop = GLib.MainLoop()
    mainloop.run()
    pass


def register_ad_cb():
    print("SDP register success")


def register_ad_error_cb(error):
    print('Error: Failed to register sdp:', str(error))
    quit()


main()
