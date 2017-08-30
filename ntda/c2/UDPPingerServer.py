#!/usr/bin/env python

import random
import socket

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serverSocket.bind(('', 12000))

while True:
    rand = random.randint(0, 10)
    message, address = serverSocket.recvfrom(1024)
    message = message.upper()
    if rand < 4:
        continue
    serverSocket.sendto(message, address)
