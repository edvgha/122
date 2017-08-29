#!/usr/bin/env python

import socket
import os

serverPort = 12000
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)

while True:
    print 'Ready to serve ...'
    connectionSocket, addr = serverSocket.accept()
    try:
        message = connectionSocket.recv(1024)
        filename = message.split()[1]
        f = open(filename[1:])
        sz = os.path.getsize(filename[1:])
        cl = "Content-Length: %d\r\n" % sz
        outputdata = f.readlines()
        # Send one HTTP header line into socket
        connectionSocket.send('HTTP/1.1 200 OK\r\n')
        connectionSocket.send(cl)
        connectionSocket.send('Content-Type: text/html\r\n')
        connectionSocket.send('Connection: close\r\n\r\n')
        # Send the content of the requested file to the client
        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i])
        connectionSocket.close()
    except IOError:
        print 'IOError ...'
        # Send response message for file not found
        ef = open('PageNotFound.html')
        esz = os.path.getsize('PageNotFound.html')
        ecl = "Content-Length: %d\r\n" % esz
        errordata = ef.readlines();
        connectionSocket.send('HTTP/1.1 404 Not Found\r\n')
        connectionSocket.send(ecl)
        connectionSocket.send('Content-Type: text/html\r\n')
        connectionSocket.send('Connection: close\r\n\r\n')
        for i in range(0, len(errordata)):
            connectionSocket.send(errordata[i])
        connectionSocket.close()
serverSocket.close()
