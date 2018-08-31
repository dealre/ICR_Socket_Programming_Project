import socket
import sys
import time
import threading
import multiprocessing
from queue import Queue


global message


def error(str):
    print(str)
    sys.exit(-1)


def output_f():
    while True:
        message = input()
        if message == 'q':
            break
        sock.send(message.encode())
    return


def input_f():
    while True:
        recieve = sock.recv(256)
        response = recieve.decode()
        print('Server: ' + response)
        if message == 'q':
            break
    return


if len(sys.argv) < 3:
    error('ERROR - too few arguments')

if len(sys.argv) > 3:
    error('ERROR - too many arguments')

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((sys.argv[1], int(sys.argv[2])))
message = 'temp'

threadout = threading.Thread(target=output_f)
threadin = threading.Thread(target=input_f)
threadout.daemon = True
threadin.daemon = True
threadout.start()
threadin.start()

while True:
    if message == 'q':
        break

sock.close()
sys.exit(0)
