import socket
import sys
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server = '127.0.0.1'
port = 12345
message = 'hello'

sock.connect((server, port))

sock.send('test'.encode())
time.sleep(10)







































