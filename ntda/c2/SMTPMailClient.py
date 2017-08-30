#!/usr/bin/env python

import socket

msg = "\r\n I love computer networkds!"
endmsg = "\r\n.\r\n"
# Choose a mail server (e.g. Google mail server) and call it mailserver
mailserver = #TODO
# Create socket called clientSocket and establish a TCP connection with mailserver
#TODO
recv = clientSocket.recv(1024)
print recv
if recv[:3] != '220':
    print '220 reply not received from server.'

# Send HELO command and print server response.
heloCommand = 'HELO Alice\r\n'
clientSocket.send(heloCommand)
recv1 = clientSocket.recv(1024)
print recv1
if recv1[:3] != '250':
    print '250 reply not received from server.'
# Send MAIL FROM command and print server response
#TODO
# Sent RCPT TO command and print server response
#TODO
# Sent DATA command and print server response
#TODO
# Send message data
#TODO
# Message ends with a single period
#TODO
# Send QUIT command and get server response
#TODO
