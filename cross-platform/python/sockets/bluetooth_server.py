from socket import *


def main():
    addr = "00:00:00:00:00:00"
    port = 29
    sock = None

    try:
        sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)
        sock.bind((addr, port))
        sock.listen(1)
        while True:
            c_sock, addr = sock.accept()
            print("receive connection:", addr)
            while True:
                data = c_sock.recv(8192)
                if len(data) == 0:
                    break
                print(data)
    finally:
        if sock is not None:
            sock.close()
    pass


if __name__ == '__main__':
    main()
