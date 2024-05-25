#!/usr/bin/python3

import time
from PIL import Image, ImageDraw, ImageFont

import LCDScreen


def main():
    lcd = LCDScreen.LCDScreen()
    try:
        lcd.init()
        lcd.clear()

        image = Image.open("demo.jpg")
        lcd.ShowImage(image)
        time.sleep(5)

        font = ImageFont.truetype(
            "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
            25
        )
        while True:
            image = Image.new(
                "RGB", (lcd.height, lcd.width), "WHITE"
            )
            draw = ImageDraw.Draw(image)
            msg = time.strftime(
                "%Y-%m-%d %T", time.localtime()
            )
            draw.text(
                (0, 0), msg,
                fill="BLACK", font=font
            )
            lcd.ShowImage(image)
            time.sleep(1)
    finally:
        lcd.close()
        pass


if __name__ == "__main__":
    main()
