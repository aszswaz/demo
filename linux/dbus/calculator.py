#!/usr/bin/python3
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

"""
将 Calcutor 对象映射为 dbus 对象，如果直接访问 Calcutor 对象。可能会遇到以下错误：
g-dbus-error-quark: GDBus.Error:org.freedesktop.DBus.Error.AccessDenied:......
这是因为 dbus 系统包含一个安全策略功能，允许指定用户可以访问在 SystemBus 上注册的接口，
解决这个问题的方法是创建 /etc/dbus-1/system.d/com.example.calculator.conf 文件，并写入以下内容：
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE busconfig PUBLIC
    "-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN"
    "http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>
    <policy user="aszswaz">
        <allow eavesdrop="true"/>
        <allow eavesdrop="true" send_destination="*"/>
        <allow own="com.example.calculator_interface"/>
        <allow eavesdrop="true" send_interface="com.example.calculator_interface" send_member="Add"/>
     </policy>
</busconfig>
"""


class Calcutor(dbus.service.Object):
    def __init__(self):
        self.path = "/com/example/calcutor"
        # 映射对象
        dbus.service.Object.__init__(self, dbus.SystemBus(), self.path)

    @dbus.service.method(
        "com.example.calculator_interface",
        in_signature='ii',
        out_signature='i'
    )
    def add(self, a1: int, a2: int) -> int:
        """
        add 函数被映射到 dbus 对象，
        in_signature：函数的参数类型，i 表示 int，ii 表示两个 int 参数，
        out_signature：函数的返回值类型
        """
        sum = a1 + a2
        print(a1, " + ", a2, " = ", sum)
        return sum


def main():
    mainloop = None

    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    Calcutor()

    mainloop = GLib.MainLoop()
    print("waiting for some calculations to do....")
    mainloop.run()


if __name__ == "__main__":
    main()
