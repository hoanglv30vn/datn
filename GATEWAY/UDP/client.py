import socket

HOST = 'localhost'    # Cấu hình address server
PORT = 8000              # Cấu hình Port sử dụng
d = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Cấu hình socket
d.connect((HOST, PORT)) # tiến hành kết nối đến server
d.sendall(b'Chao hoang!') # Gửi dữ liệu lên server 
data = d.recv(1024) # Đọc dữ liệu server trả về
print('Server Respone: ', repr(data))