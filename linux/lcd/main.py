#!/usr/bin/python3

import time
from PIL import Image, ImageDraw, ImageFont
import numpy

import ST7789VW


def main():
    dev = ST7789VW.ST7789VW()
    try:
        dev.init()
        dev.clear()

        # 加载背景图片
        original_img = Image.open("demo.jpg")
        width, height = original_img.size
        # 是否需要横向显示图片
        horizontal = width > height
        # 如果图片的分辨率大于屏幕的分辨率，则调整图片的分辨率以适应屏幕
        if width * height > dev.width * dev.height:
            if horizontal:
                original_img = original_img.resize((dev.height, dev.width))
            else:
                original_img = original_img.resize((dev.width, dev.height))

        font = ImageFont.truetype(
            "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
            25
        )
        while True:
            # 在图片上写入当前时间
            new_img = original_img.copy()
            draw = ImageDraw.Draw(new_img)
            msg = time.strftime(
                "%Y-%m-%d %T", time.localtime()
            )
            draw.text(
                (0, 0), msg,
                fill="BLACK", font=font
            )
            dev.show_image(new_img, horizontal)
            time.sleep(0.5)
    finally:
        dev.close()
        pass


if __name__ == "__main__":
    main()
