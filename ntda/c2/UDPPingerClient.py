#!/usr/bin/env python
import socket
import time

serverName = 'localhost'
serverPort = 12000

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
clientSocket.bind(('', 5432))
clientSocket.settimeout(1)

for i in range(0, 10):
    t = time.ctime();
    message = "Ping "+ `i` + " " + `t`
    t1 = time.time()
    clientSocket.sendto(message, (serverName, serverPort))
    try:
        responseMessage, serverAddress = clientSocket.recvfrom(2048)
        t2 = time.time()
        rtt = t2 - t1
        print responseMessage
        print rtt
    except socket.timeout:
        print 'Request timed out'
clientSocket.close()
