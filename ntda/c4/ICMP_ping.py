#!/usr/bin/env python 

import socket
import os
import sys
import struct
import time
import select
import binascii

ICMP_ECHO_REQUEST = 8

def checksum(str):
    csum = 0
    countTo = (len(str) / 2) * 2
    count = 0
    while count < countTo:
        thisVal = ord(str[count + 1]) * 256 + ord(str[count])
        csum = csum + thisVal
        csum = csum & 0xffffffffL
        count = count + 2

    if countTo < len(str):
        csum = csum + ord(str[len(str) - 1])
        csum = csum & 0xffffffffL

    csum = (csum >> 16) + (csum & 0xffff)
    csum = csum + (csum >> 16)
    answer = ~csum
    answer = answer & 0xffff
    answer = answer >> 8 | (answer << 8 & 0xff00)
    return answer

def receiveOnePing(mySocket, ID, timeout, destAddr):
    timeLeft = timeout
    while 1:
        startedSelect = time.time()
        whatReady = select.select([mySocket], [], [], timeLeft)
        howLongInSelect = (time.time() - startedSelect)

        if whatReady[0] == [] : #Timeout
            return "Request timed out.0"
        timeReceived = time.time()
        recPacket, addr = mySocket.recvfrom(1024)
        #Fetch the ICMP header from the IP packet
        t, c, ch, ix, seq, b = struct.unpack_from("bbHHhd",recPacket, 20);
        if ID != ix or c != 0 or t != 0 or seq != 1 or checksum(recPacket[20]) != 0xffff:
            return "The shit got up ...."
        #print 'Unpacked data:', t, c, ch, ix, seq, b
        timeLeft = timeLeft - howLongInSelect
        if timeLeft <= 0:
            return "Request timed out.1"
        return howLongInSelect

def sendOnePing(mySocket, destAddr, ID):
    #Header is type (8), code (8), checksum (16), id (16), sequence (16)
    myChecksum = 0
    #Make a dummy header with a 0 checksum
    #struct -- Interpret strings as packed binary data
    header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
    data = struct.pack("d", time.time())
    #Calculate the checksum on the data and the dummy header
    myChecksum = checksum(header + data)
    if sys.platform == 'darwin':
        myChecksum = socket.htons(myChecksum) & 0xffff
        #Convert 16-bit integers from host to network byte order
    else:
        myChecksum = socket.htons(myChecksum)

    header = struct.pack("bbHHh", ICMP_ECHO_REQUEST, 0, myChecksum, ID, 1)
    packet = header + data
    
    mySocket.sendto(packet, (destAddr, 1)) #AF_INET address must be tuple, not str

def doOnePing(destAddr, timeout):
    icmp = socket.getprotobyname("icmp")
    #Create Socket here
    mySocket = socket.socket(socket.AF_INET, socket.SOCK_RAW, icmp)
    myID = os.getpid() & 0xffff #Return the current process id
    sendOnePing(mySocket, destAddr, myID)
    delay = receiveOnePing(mySocket, myID, timeout, destAddr)
    mySocket.close()
    return delay

def ping(host, timeout = 1):
    #timeout = 1 means: If one second goes by without a reply from the server,
    #the client assumes that either the client's ping or the server's pong is lost
    dest = socket.gethostbyname(host)
    print "Pinging " + dest + " using Python:"
    print ""
    while 1 :
        delay = doOnePing(dest, timeout)
        print delay
        time.sleep(1) #one second
    return delay

ping ('yahoo.com')
