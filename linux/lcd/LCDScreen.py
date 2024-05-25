import time

import numpy

from gpiozero import DigitalOutputDevice, PWMOutputDevice
import spidev


class LCDScreen:

    width = 240
    height = 320

    def __init__(self) -> None:
        # 复位键
        self.PIN_RST = DigitalOutputDevice(
            27, active_high=True, initial_value=False
        )
        # data or command，0 表示 command，1 表示 data
        self.PIN_DC = DigitalOutputDevice(
            25, active_high=True, initial_value=False
        )
        # 背光控制端口
        self.PIN_BL = PWMOutputDevice(18, frequency=1000)
        self.PIN_BL.value = 50 / 100

        # 初始化 SPI 通信
        self.SPI = spidev.SpiDev(0, 0)
        # SPI 数据传输速率
        self.SPI.max_speed_hz = 40000000
        self.SPI.mode = 0
        pass

    def init(self):
        """
        初始化 LCD 屏幕
        """
        self._reset()

        self._command(0x36)
        self._data(0)

        self._command(0x3A)
        self._data(0x05)

        self._command(0x21)

        self._command(0x2A)
        self._data(0x00)
        self._data(0x00)
        self._data(0x01)
        self._data(0x3F)

        self._command(0x2B)
        self._data(0x00)
        self._data(0x00)
        self._data(0x00)
        self._data(0xEF)

        self._command(0xB2)
        self._data(0x0C)
        self._data(0x0C)
        self._data(0x00)
        self._data(0x33)
        self._data(0x33)

        self._command(0xB7)
        self._data(0x35)

        self._command(0xBB)
        self._data(0x1F)

        self._command(0xC0)
        self._data(0x2C)

        self._command(0xC2)
        self._data(0x01)

        self._command(0xC3)
        self._data(0x12)

        self._command(0xC4)
        self._data(0x20)

        self._command(0xC6)
        self._data(0x0F)

        self._command(0xD0)
        self._data(0xA4)
        self._data(0xA1)

        self._command(0xE0)
        self._data(0xD0)
        self._data(0x08)
        self._data(0x11)
        self._data(0x08)
        self._data(0x0C)
        self._data(0x15)
        self._data(0x39)
        self._data(0x33)
        self._data(0x50)
        self._data(0x36)
        self._data(0x13)
        self._data(0x14)
        self._data(0x29)
        self._data(0x2D)

        self._command(0xE1)
        self._data(0xD0)
        self._data(0x08)
        self._data(0x10)
        self._data(0x08)
        self._data(0x06)
        self._data(0x06)
        self._data(0x39)
        self._data(0x44)
        self._data(0x51)
        self._data(0x0B)
        self._data(0x16)
        self._data(0x14)
        self._data(0x2F)
        self._data(0x31)
        self._command(0x21)

        self._command(0x11)

        self._command(0x29)
        pass

    def SetWindows(self, Xstart, Ystart, Xend, Yend):
        # set the X coordinates
        self._command(0x2A)
        # Set the horizontal starting point to the high octet
        self._data(Xstart >> 8)
        # Set the horizontal starting point to the low octet
        self._data(Xstart & 0xff)
        # Set the horizontal end to the high octet
        self._data(Xend >> 8)
        # Set the horizontal end to the low octet
        self._data((Xend - 1) & 0xff)

        # set the Y coordinates
        self._command(0x2B)
        self._data(Ystart >> 8)
        self._data((Ystart & 0xff))
        self._data(Yend >> 8)
        self._data((Yend - 1) & 0xff)

        self._command(0x2C)

    def ShowImage(self, Image, Xstart=0, Ystart=0):
        """Set buffer to value of Python Imaging Library image."""
        """Write display buffer to physical display"""
        imwidth, imheight = Image.size
        if imwidth == self.height and imheight == self.width:
            img = numpy.asarray(Image)
            pix = numpy.zeros(
                (self.width, self.height, 2), dtype=numpy.uint8)
            # RGB888 >> RGB565
            pix[..., [0]] = numpy.add(numpy.bitwise_and(
                img[..., [0]], 0xF8), numpy.right_shift(img[..., [1]], 5))
            pix[..., [1]] = numpy.add(numpy.bitwise_and(numpy.left_shift(
                img[..., [1]], 3), 0xE0), numpy.right_shift(img[..., [2]], 3))
            pix = pix.flatten().tolist()

            self._command(0x36)
            self._data(0x70)
            self.SetWindows(0, 0, self.height, self.width)
            self.PIN_DC.on()
            for i in range(0, len(pix), 4096):
                self._write(pix[i:i+4096])

        else:
            img = numpy.asarray(Image)
            pix = numpy.zeros(
                (imheight, imwidth, 2), dtype=numpy.uint8)

            pix[..., [0]] = numpy.add(numpy.bitwise_and(
                img[..., [0]], 0xF8), numpy.right_shift(img[..., [1]], 5))
            pix[..., [1]] = numpy.add(numpy.bitwise_and(numpy.left_shift(
                img[..., [1]], 3), 0xE0), numpy.right_shift(img[..., [2]], 3))

            pix = pix.flatten().tolist()

            self._command(0x36)
            self._data(0x00)
            self.SetWindows(0, 0, self.width, self.height)
            self.PIN_DC.on()
            for i in range(0, len(pix), 4096):
                self._write(pix[i:i+4096])

    def clear(self):
        """Clear contents of image buffer"""
        _buffer = [0xff]*(self.width * self.height * 2)
        self.SetWindows(0, 0, self.height, self.width)
        self.PIN_DC.on()
        for i in range(0, len(_buffer), 4096):
            self._write(_buffer[i:i+4096])

    def close(self):
        self.SPI.close()
        self.PIN_RST.on()
        self.PIN_DC.off()
        self.PIN_BL.close()
        time.sleep(0.001)

    def _reset(self):
        self.PIN_RST.on()
        time.sleep(0.01)
        self.PIN_RST.off()
        time.sleep(0.01)
        self.PIN_RST.on()
        pass

    def _command(self, cmd):
        self.PIN_DC.off()
        self._write([cmd])
        pass

    def _data(self, data):
        self.PIN_DC.on()
        self._write([data])
        pass

    def _write(self, value):
        self.SPI.writebytes(value)
        pass
    pass
