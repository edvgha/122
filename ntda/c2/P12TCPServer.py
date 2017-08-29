#!/usr/bin/env python

import sys
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(1)
connectionSocket, addr = serverSocket.accept()
while 1:
    sentence = connectionSocket.recv(1024)
    print sentence,'\n'
    sentence = ''
    print 'xxx'
connectionSocket.close()
