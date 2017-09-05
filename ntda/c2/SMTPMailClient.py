#!/usr/bin/env python

import socket
import base64

# Choose a mail server (e.g. Google mail server) and call it mailserver
mailserver = 'smtp.comcast.net'
#port = 587
port = 25
# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((mailserver, port))
recv = clientSocket.recv(1024)
print recv
if recv[:3] != '220':
    print '220 reply not received from server.'

# Send HELO command and print server response.
heloCommand = 'HELO edvard_gh@comcast.net\r\n'
clientSocket.send(heloCommand)
recv1 = clientSocket.recv(1024)
print recv1
if recv1[:3] != '250':
    print '250 reply not received from server.'
authLogin = 'AUTH LOGIN\r\n'
clientSocket.send(authLogin)
recv2 = clientSocket.recv(1024)
print recv2
if recv2[:3] != '334':
    print '334 reply not received from server'
# edvard_gh encoded with base64
username = 'ZWR2YXJkX2do\r\n'
clientSocket.send(username)
recv3 = clientSocket.recv(1024)
print recv3
if recv3[:3] != '334':
    print '334 reply not received from server'
# edvgha08 encoded with base64
password = 'ZWR2Z2hhMDg=\r\n'
clientSocket.send(password)
recv4 = clientSocket.recv(1024)
print recv4
if recv4[:3] != '235':
    print '235 reply not received from server'
# Send MAIL FROM command and print server response
mailFrom = 'MAIL FROM: <edvard_gh@comcast.net>\r\n'
clientSocket.send(mailFrom)
recv5 = clientSocket.recv(1024)
print recv5
if recv5[:3] != '250':
    print '250 reply not received from server'
# Sent RCPT TO command and print server response
rcptTo = 'RCPT TO: <edvard_gh@yahoo.com>\r\n'
clientSocket.send(rcptTo)
recv5 = clientSocket.recv(1024)
print recv5
if recv5[:3] != '250':
    print '250 reply not received from server'
# Sent DATA command and print server response
data = 'DATA\r\n'
clientSocket.send(data)
recv6 = clientSocket.recv(1024)
print recv6
if recv6[:3] != '354':
    print '354 reply not received from server'
# Send message data
# Message ends with a single period
msg = "\r\n I love computer networkds!"
endmsg = "\r\n.\r\n"
clientSocket.send(msg)
clientSocket.send(endmsg)
recv7 = clientSocket.recv(1024)
print recv7
if recv7[:3] != '250':
    print '250 reply not received from server'
# Send QUIT command and get server response
quit = 'QUIT\r\n'
clientSocket.send(quit)
recv8 = clientSocket.recv(1024)
print recv8
if recv8[:3] != '221':
    print '221 reply not received from server'
