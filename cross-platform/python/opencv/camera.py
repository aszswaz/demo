#!/usr/bin/python3
import cv2


def main():
    vid = cv2.VideoCapture(0)
    while True:
        _, frame = vid.read()
        cv2.imshow("frame", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    vid.release()
    cv2.destroyAllWindows()
    return None


if __name__ == "__main__":
    main()
