#!/usr/bin/env python 

from socket import *

serverName = 'localhost'
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
while 1:
    sentence = raw_input()
    print 'sent msg', sentence
    clientSocket.send(sentence)
clientSocket.close()
