#!/usr/bin/python3

import dbus
import dbus.mainloop.glib
from gi.repository import GLib

mainloop = None


def greeting_signal_received(greeting):
    print(greeting)


def main():
    # python3-dbus 使用 GLib 的 MainLoop API
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    bus = dbus.SystemBus()
    """
    由接口 com.example.greeting 发出 GreetingSignal 的信号，通过回调传递到函数 greeting_signal_received，
    我们知道该信号包含一个字符串函数，因为这是规范的一部分，因此我们的回调函数适应了这一点。
    使用 dbus-send 发送信号和参数：
    dbus-send --system --type=signal / com.example.greeting.GreetingSignal string:"hello"
    """
    bus.add_signal_receiver(
        greeting_signal_received,
        dbus_interface="com.example.greeting",
        signal_name="GreetingSignal"
    )
    # 创建事件循环
    mainloop = GLib.MainLoop()
    # 阻塞线程循环监听 dbus 事件
    mainloop.run()


if __name__ == "__main__":
    main()
