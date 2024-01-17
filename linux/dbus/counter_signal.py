#!/usr/bin/python3
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib
import time

mainloop = None


class Counter(dbus.service.Object):
    def __init__(self, bus):
        self.path = '/com/example/counter'
        self.c = 0
        dbus.service.Object.__init__(self, bus, self.path)

    @dbus.service.signal('com.example.Counter')
    def counterSignal(self, counter):
        """
        dbus.service.signal 注解将 python 函数与 dbus signal 绑定，程序所有对该函数的调用都会被转换为 dbus signal 并发送出去。
        """
        pass

    def emitCounterSignal(self):
        self.counterSignal(self.c)

    def increment(self):
        self.c = self.c + 1
        print(self.c)


dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
bus = dbus.SystemBus()
counter = Counter(bus)
while True:
    counter.increment()
    counter.emitCounterSignal()
    time.sleep(1)
