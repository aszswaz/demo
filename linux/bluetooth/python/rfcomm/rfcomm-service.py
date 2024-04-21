#!/usr/bin/env python3
"""PyBluez simple example rfcomm-server.py

Simple demonstration of a server application that uses RFCOMM sockets.

Author: Albert Huang <albert@csail.mit.edu>
$Id: rfcomm-server.py 518 2007-08-10 07:20:07Z albert $
"""

import time

import bluetooth

server_sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
server_sock.bind(("", bluetooth.PORT_ANY))
server_sock.listen(1)

port = server_sock.getsockname()[1]

uuid = "94f39d29-7d6d-437d-973b-fba39e49d4ee"

bluetooth.advertise_service(
    server_sock, "SampleServer", service_id=uuid,
    service_classes=[uuid, bluetooth.SERIAL_PORT_CLASS],
    profiles=[bluetooth.SERIAL_PORT_PROFILE],
)

print("Waiting for connection on RFCOMM channel", port)

client_sock, client_info = server_sock.accept()
print("Accepted connection from", client_info)

try:
    lastTime = int(time.time())
    total = 0
    lastTotal = 0
    while True:
        data = client_sock.recv(8192)
        if not data:
            break
        total = total + len(data)
        ctime = int(time.time())
        if ctime > lastTime:
            lastTime = ctime
            speed = (total - lastTotal) / 1024
            print("\rspeed:", speed, "kb", end="")
            lastTotal = total
except OSError:
    pass

print("Disconnected.")

client_sock.close()
server_sock.close()
print("All done.")
