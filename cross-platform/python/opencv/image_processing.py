#!/usr/bin/python3

import cv2

"""
使用 opencv 处理图片
"""


def main():
    # 读取图片
    img = cv2.imread("image01.jpg")
    # 去除图片的颜色，得到灰白图
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # 将图片显示到窗口
    cv2.imshow("image01", img)
    # 阻塞程序
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    pass


if __name__ == '__main__':
    main()
