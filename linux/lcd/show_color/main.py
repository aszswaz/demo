#!/usr/bin/python3

import signal

from PIL import Image, ImageDraw

import ST7789VW

dev = ST7789VW.ST7789VW()


def main():
    try:
        dev.init()
        dev.clear()

        signal.signal(signal.SIGINT, signalExit)
        signal.signal(signal.SIGHUP, signalExit)
        signal.signal(signal.SIGTERM, signalExit)

        size = (dev.height, dev.width)
        imgs = [
            Image.new(mode="RGB", size=size, color="RED"),
            Image.new(mode="RGB", size=size, color="ORANGE"),
            Image.new(mode="RGB", size=size, color="YELLOW"),
            Image.new(mode="RGB", size=size, color="GREEN"),
            Image.new(mode="RGB", size=size, color="CYAN"),
            Image.new(mode="RGB", size=size, color="BLUE"),
            Image.new(mode="RGB", size=size, color="PURPLE")
        ]
        while True:
            for item in imgs:
                dev.horizontal(item)

        signal.pause()
    finally:
        dev.close()
    pass


def signalExit(sig, frame):
    dev.close()


if __name__ == "__main__":
    main()
