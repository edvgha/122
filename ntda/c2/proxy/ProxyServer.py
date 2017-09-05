#!/usr/bin/env python
#TODO works only for HTTP

import socket
import sys


def forwardRequest(fileobj, message):
    print 'forward message ...'
    items = message.splitlines()
    for item in items:
        fileobj.write(item + '\r\n')
    fileobj.write('\r\n')

def readResponse(fileobj):
    l = fileobj.readline()
    buf = l
    contentLength = 0
    while l != '\r\n' and l != '\n':
        l = fileobj.readline()
        buf += l
        if l.split(':')[0].lower() == 'Content-Length'.lower():
            contentLength = int(l.split(':')[1])
    buf += fileobj.read(contentLength)
    return buf

def fileNotFound(tcpCliSock):
    header = ''
    header += 'HTTP/1.1 404 Not Found\r\n'
    header += 'Content-Length: 112\r\n'
    header += 'Content-Type: text/html\r\n'
    header += 'Connection: close\r\n\r\n'
    body = ''
    body += '<header><title>Error404</title></header>\n'
    body += '<body bgcolor=""ffffff"">\n'
    body += 'Server couldn\'t find this file'
    body += '</body>\n</html>'
    tcpCliSock.send(header)
    tcpCliSock.send(body)


if len(sys.argv) <= 1:
    print 'Usage : "./ProxyServer.py server_ip"\n[server_ip : It is the IP Address Of Proxy Server'
    sys.exit(2)

# Create a server socket, bind it to a port and start listening
tcpSerSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serPort = int(sys.argv[1])
tcpSerSock.bind(('',serPort))
tcpSerSock.listen(1)
while 1:
    # Start receiving data from the client
    print 'Ready to serve ...'
    tcpCliSock, addr = tcpSerSock.accept()
    print 'Received a connection from:', addr
    message = tcpCliSock.recv(1024)
    print message
    # Extract the filename from the given message
    print message.split()[1]
    filename = message.split()[1].split("/")[2]
    fileExist = "false"
    filetouse = message.split()[1][7:].replace("/","_",1)
    try:
        # Check wether the file exist in the cache
        f = open(filetouse, "r")
        outputdata = f.readlines()
        fileExist = "true"
        # ProxyServer finds a cache hit and generates a response message
        for d in outputdata:
            tcpCliSock.send(d)
        f.close()
    # Error handling for file not found in cache
    except IOError:
        if fileExist == "false":
            # Create a socket on the proxyserver
            c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            hostn = filename.replace("www.","",1)
            print 'hostn: ', hostn
            try:
                # Connect to the socket to port 80
                c.connect((hostn, 80))
                # Create a temporary file on this socket and ask port 80
                # for the file requested by the client
                fileobj = c.makefile('r', 0)
                forwardRequest(fileobj, message)
                # Read the response into buffer
                buf = readResponse(fileobj)
                # Create a new file in the cache for the requested file.
                # Also send the response in the buffer to client socket
                # and the corresponding file in the cache
                tcpCliSock.send(buf)
                tmpFile = open("./" + filetouse, "wb")
                tmpFile.write(buf)
                tmpFile.close()
                fileobj.close()
            except:
                print "Illegal request"
            c.close()
        else:
            # HTTP response message for file not found
            fileNotFound(tcpCliSock)
    # Close the client and the server sockets
    tcpCliSock.close()
tcpSerSock.close()
