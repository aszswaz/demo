#!/usr/bin/python3

"""
用 opencv 实现人脸识别
"""

import cv2

# 加载人脸分类器
face_detect = cv2.CascadeClassifier("haarcascade_frontalface_alt2.xml")


def main():
    # 读取摄像头
    video = None

    try:
        # 打开摄像头
        video = cv2.VideoCapture(0)
        while True:
            # 读取摄像头
            flag, frame = video.read()
            if not flag:
                break
            scan_faces(frame)
            # 将图片显示到窗口
            cv2.imshow("result", frame)
            if ord("q") == cv2.waitKey(1):
                break
    finally:
        if video is not None:
            video.release()
        cv2.destroyAllWindows()
    pass


def scan_faces(frame):
    """
    扫描图像中的人脸
    """
    # 去除图像的颜色，得到灰白图
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 扫描人脸
    face = face_detect.detectMultiScale(gray_frame)
    # 输出扫描结果
    for x, y, w, h in face:
        cv2.rectangle(frame, (x, y), (x + w, y + h), color=(0, 0, 255), thickness=2)


if __name__ == '__main__':
    main()
