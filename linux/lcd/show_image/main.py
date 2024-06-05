#!/usr/bin/python3

import signal
import sys
import os
from PIL import Image

import ST7789VW

dev = ST7789VW.ST7789VW()


def main():
    try:
        work_dir = os.path.realpath(sys.argv[0])
        work_dir = os.path.dirname(work_dir)
        os.chdir(work_dir)

        dev.init()
        dev.clear()

        signal.signal(signal.SIGINT, signalExit)
        signal.signal(signal.SIGHUP, signalExit)
        signal.signal(signal.SIGTERM, signalExit)

        # 加载背景图片
        img = Image.open("demo.jpg")
        width, height = img.size
        horizontal = width > height
        # 如果图片的分辨率大于屏幕的分辨率，则调整图片的分辨率以适应屏幕
        if width * height > dev.width * dev.height:
            if horizontal:
                img = img.resize((dev.height, dev.width))
            else:
                img = img.resize((dev.width, dev.height))

        if horizontal:
            dev.horizontal(img)
        else:
            dev.vertical(img)
        signal.pause()
    finally:
        dev.close()
        pass


def signalExit(sig, frame):
    dev.close()


if __name__ == "__main__":
    main()
