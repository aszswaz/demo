#!/bin/python3

import socket


def main():
    port = 28
    server_sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
    server_sock.bind((socket.BDADDR_ANY, port))
    server_sock.listen(1)

    client_sock, addr = server_sock.accept()
    print(addr)

    server_sock.close()
    pass


main()
