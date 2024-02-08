from socket import *

import cv2
import numpy


def main():
    sock = None
    try:
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
        sock.connect(("localhost", 8080))

        while True:
            data = sock.recv(921600)
            data = numpy.frombuffer(data, dtype="uint8")
            img = cv2.imdecode(data, 1)
            img = img.reshape(480, 640, 3)
            cv2.imshow('server_frame', img)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
    finally:
        if sock is not None:
            sock.close()
    pass


if __name__ == '__main__':
    main()
