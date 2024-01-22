from socket import *


def main():
    addr = "B0:3C:DC:C7:8E:A8"
    port = 29
    sock = None

    try:
        sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)
        sock.connect((addr, port))
        sock.sendall(b"Hello World")
    finally:
        if sock is not None:
            sock.close()
    pass


if __name__ == '__main__':
    main()
