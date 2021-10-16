import socket
import errno
import sys
import threading
import time
import serial

exitFlag = 0
global flagsenduart 
flagsenduart=0

global serial__ 
global data
data='hi'
# serial__=serial.Serial()
serial_com = input("SELLECT COM: ")
serial__=serial.Serial(serial_com, baudrate=9600 ,timeout=0.1)

HEADER_LENGTH = 40

IP = "127.0.0.1"
PORT = 1234
# my_username = input("Username: ")
my_username = input("tên node: ")

# Create a socket
# socket.AF_INET - address family, IPv4, some otehr possible are AF_INET6, AF_BLUETOOTH, AF_UNIX
# socket.SOCK_STREAM - TCP, conection-based, socket.SOCK_DGRAM - UDP, connectionless, datagrams, socket.SOCK_RAW - raw IP packets
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to a given ip and port
client_socket.connect((IP, PORT))

# Set connection to non-blocking state, so .recv() call won;t block, just return some exception we'll handle
client_socket.setblocking(False)

# Prepare username and header and send them
# We need to encode username to bytes, then count number of bytes and prepare header of fixed size, that we encode to bytes as well
username = my_username.encode('utf-8')
username_header = f"{len(username):<{HEADER_LENGTH}}".encode('utf-8')
client_socket.send(username_header + username)




class chaylen (threading.Thread):
    def __init__(self,  threadID, name ):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
    def run(self):
        print ("Bat dau " + self.name)
        self.readData()

    # def readData():
    #     if serial__.in_waiting >0:
    #         data = serial__.readline()
    #         data = data.decode('utf-8')
    #         print(data)   
    #         data = (data[data.find('LENGHT')+6:data.find('LENGHT')+8])
    #         print(data)   
    def senddata(tt):   
        if (tt==1):
            hello= 'on' + '.'
        else:
            hello='off' + '.'
        serial__.write(hello.encode())       
        print(hello.encode())    
        # read_sockets, _, exception_sockets = select.select(sockets_list, [], sockets_list)    
        # for notified_socket in read_sockets:

        
       
        # pass

       
    def readData(self):
        while True: 
            # print("wait data")
            if serial__.in_waiting >0:
                global data
                data = serial__.readline()
                data = data.decode('utf-8')
                # print(data)   
                # data = (data[data.find('LENGHT')+6:data.find('LENGHT')+8])
                print(data)    
                message = data.encode('utf-8')
                message_header = f"{len(data):<{HEADER_LENGTH}}".encode('utf-8')
                client_socket.send(message_header + message)                                        

class udp (threading.Thread):
    def __init__(self,  threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        # self.counter = counter
    def run(self):
        print ("Bat dau " + self.name)
        self.udp_truyen_nhan()
    def udp_truyen_nhan(self):
        while True:
        
            try:
            # Now we want to loop over received messages (there might be more than one) and print them
                while True:

                    # # Receive our "header" containing username length, it's size is defined and constant
                    # username_header = client_socket.recv(HEADER_LENGTH)

                    # # If we received no data, server gracefully closed a connection, for example using socket.close() or socket.shutdown(socket.SHUT_RDWR)
                    # if not len(username_header):
                    #     print('Connection closed by the server')
                    #     sys.exit()

                    # # Convert header to int value
                    # username_length = int(username_header.decode('utf-8').strip())

                    # # Receive and decode username
                    # username = client_socket.recv(username_length).decode('utf-8')

                    # Now do the same for message (as we received username, we received whole message, there's no need to check if it has any length)
                    message_header = client_socket.recv(HEADER_LENGTH)
                    message_length = int(message_header.decode('utf-8').strip())
                    message = client_socket.recv(message_length).decode('utf-8')
                    serial__.write(message.encode())       
                    print(message.encode())
                    # Print message
                    print("chao")
                    print(f'{message}')

            except IOError as e:
                # This is normal on non blocking connections - when there are no incoming data error is going to be raised
                # Some operating systems will indicate that using AGAIN, and some using WOULDBLOCK error code
                # We are going to check for both - if one of them - that's expected, means no incoming data, continue as normal
                # If we got different error code - something happened
                if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                    print('Reading error: {}'.format(str(e)))
                    # sys.exit()

                # We just did not receive anything
                continue

            except Exception as e:
                # Any other exception - something happened, exit
                print('Reading error: '.format(str(e)))
                # sys.exit()
                pass

try:
    thread1 = chaylen(1, "Thread-1")
    thread2 = udp(2, "Thread-2")# Bat dau cac thread moi
    thread1.start()
    thread2.start()
    print ("Ket thuc Main Thread")
except:
    print("error")                