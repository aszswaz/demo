#!/usr/bin/python3

import v4l2
import os
import fcntl


def main():
    camera = None
    try:
        camera = os.open("/dev/video0", os.O_RDWR)
        cp = v4l2.v4l2_capability()
        fcntl.ioctl(camera, v4l2.VIDIOC_QUERYCAP, cp)
        print(cp.driver)
        print(cp.card)
    finally:
        if camera is not None:
            os.close(camera)
    return None


if __name__ == "__main__":
    main()
