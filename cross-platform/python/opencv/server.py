#!/usr/bin/python3
from socket import *

import cv2
import numpy

"""
通过 opencv 打开摄像头，通过 socket 进行传输视频流
"""


def main():
    video = None
    sock = None
    try:
        video = cv2.VideoCapture(0)
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
        sock.bind(("0.0.0.0", 8080))
        sock.listen(10)
        while True:
            print("waiting for connection...")
            c_sock, addr = sock.accept()
            print(f"{addr[0]}: connection succeeded")
            send_img(video, c_sock)
    finally:
        if video is not None:
            video.release()
        if sock is not None:
            sock.close()


def send_img(video: cv2.VideoCapture, sock: socket):
    while True:
        _, frame = video.read()
        _, data = cv2.imencode(".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, 50])
        sock.sendall(data)


if __name__ == '__main__':
    main()
