#################################################################################### 
##                                           ``..``                               ##    
##                                         -ymNMNmds:`                            ##     
##                                 `.:/+osyMMMNmNMMMMms:                          ##     
##                             `:sdNMMMMMMMMMy.  .+hNMMMd/                        ##     
##                           :yNMMMMNdyso+++-       `+mMMMd:                      ##     
##                         /mMMMNy/.                   /NMMMo                     ##     
##                       .hMMMd+`                       .hMMMo                    ##     
##               -yyyyyyyNMMMMhyyyyyyyyyyyyyyyyyyyyyyyyyyhMMMM/                   ##     
##               :NMMMMMMMMMMddMmdNm...mMMMMMMMMMMNdmMddMNNMMMm                   ##     
##                .sdMMMMMNmdmmdmNmh   ydMMMMMMMNddNmdNNd/.yMMM:                  ##     
##                 ``yNMMMdmMmdMmh-`   `.hmMMMMmdNNdmMhs`  +MMM+                  ##     
##                   `NMMNssssss:         :sssssssssss`    /MMMo                  ##     
##                   :MMMy     .+/`         ..             oMMM+                  ##     
##                   /MMMo     :NMd/.   `.:ymd.            hMMM.                  ##     
##                   -MMMh      -yNMmhyydmMNh/            :MMMh                   ##     
##                    dMMN-       ./shddys/.            `oNMMm-                   ##     
##                    :NMMm-                         `.omMMMh.                    ##     
##                     /NMMNo.                  ``.:sdNMMNd/                      ##     
##                      -hMMMNho/-.``````..-:+oyhmMMMMNms-                        ##     
##                        :yNMMMMMN HOANGLE MMMMMMNds/-                           ##     
##                           -+shdmNNMMMMmdhyso/:.                                ##     
##                                  `MMMm                                         ##     
##                                  /MMMo                                         ##     
##           .`                     yMMM-                                         ##     
##     .----oNm`                    mMMN                                          ##     
##    -mNNNNMMMy.                  .MMMh                                          ##     
##     .../MMMMMm+`              `/yMMMo                                          ##     
##         :oydMMMm/           -smMMMMMo                                          ##     
##            `+mMMNs`       .yNMMMMMMMNy.                                        ##     
##              .hMMMh.     /mMMNh:dMMMMMm/                                       ##     
##               `sMMMd.  `yMMMm/  mMMMdMMNs`                                     ##     
##                 sMMMh`-dMMMh.   NMMN`yMMMh.                                    ##     
##                 `yMMMhmMMMo`    NMMN  +NMMd-                                   ##     
##                  `yMMMMMMy      NMMN   /NMMm-                                  ##     
##                   `hMMMMM-      dMMM`   :NMMm.                                 ##     
##                    `dMMMs       yMMM-    /MMMd`                                ##     
##                     `/+:        oMMM+     oMMMs                                ##     
##                                 -MMMh      dMMM:                               ##
#################################################################################### 
# -*- coding: utf-8 -*-
# Form implementation generated from reading ui file 'untitled.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.
from PyQt5 import QtCore, QtGui, QtWidgets
import sqlite3
import threading
import time
import datetime
import socket
import sys
import glob
import serial
from threading import Thread
from PyQt5.QtCore import QDate, Qt
import pyrebase
############################# DATABASE SQL #########################################
conn = sqlite3.connect('datasql.db')   #kết nối tới database
curr = conn.cursor()    #con trỏ
curr.execute('''CREATE TABLE IF NOT EXISTS CONFIG_GW(ATTRIBUTES char[30], THONGTIN char[20])''') 
curr.execute('''CREATE TABLE IF NOT EXISTS DATA_NODE(ID_NODE char[20], NAME_ID_NODE char[20], PHANLOAI CHAR[20], ID_THIETBI CHAR[20], NAME_THIETBI CHAR[20])''') 
conn.commit()


#################################################################################### 
# khởi tạo com
global serial__ 
serial__=serial.Serial()

# sau này thêm cái check xem đã lưu id của gw ở sql chưa <tích xanh :v>
name_gw = 'gateway'
curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'name_gw' ")
if (len(curr.fetchall())>0): 
    thongtin_cfig=curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'name_gw' ")
    name_gw = thongtin_cfig.fetchone()[1]
else:
    name_gw = input("nhập name gw:")
    curr.execute("INSERT INTO CONFIG_GW VALUES (?,?)",["name_gw",name_gw])# name_gw  
    conn.commit()    
print (f'name cua gw là: {name_gw}')


id_gw = 'gateway'
curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'id_gw' ")
if (len(curr.fetchall())>0): 
    thongtin_cfig=curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'id_gw' ")
    id_gw = thongtin_cfig.fetchone()[1]
else:
    id_gw = input("nhập id gw - 4 số tự nhiên:")
    curr.execute("INSERT INTO CONFIG_GW VALUES (?,?)",["id_gw",id_gw])# name_gw  
    conn.commit()    
print (f'id cua gw là: {id_gw}')

# cấu hình firebase 
firebaseConfig = {
  'apiKey': "AIzaSyAEqi81NFMPBJGxWRy7QtQv961efPzL9LA",
  'authDomain': "hellodatn.firebaseapp.com",
  'databaseURL': "https://hellodatn-default-rtdb.asia-southeast1.firebasedatabase.app",
  'projectId': "hellodatn",
  'storageBucket': "hellodatn.appspot.com",
  'messagingSenderId': "559705579450",
  'appId': "1:559705579450:web:3421e5377912259256c783",
  'measurementId': "G-YK901S5FXQ"
}
firebase = pyrebase.initialize_app(firebaseConfig)
db = firebase.database()
# firebase = pyrebase.initialize_app(firebaseConfig)
# db=firebase.database()
# data={"name":"Hoàng", 'age':22, 'addr': 'Ha Tinh'}
# db.push(data)
# db.child('infor').set(data)
# db.child('infor').set({'addr':'binh duong'})


#################################################################################### 
class Ui_MainWindow(object):
    def stream_handler(self, message):
        # hàm lắng nghe sự kiện từ firebase
        print('data thay doi tu firebase:')     
        event_fb = message["event"] # put
        print("event:" + event_fb)
        path_fb = message["path"] # /-K7yGTTEp7O549EzTYtI
        print("path:" + path_fb)      
        mess_fb = message["data"] # {'title': 'Pyrebase', "body": "etc..."}   
        # print(mess_fb['thietbi2'])
        # self.senddata(message["data"]) 
        # đường dẫn lever
        # danh sách:
        link = path_fb.count('/')
        if link == 2:
            id_node = path_fb[1:path_fb.find('/', 1)]
            id_device = path_fb[path_fb.find('/thietbi')+8:len(path_fb)]
            tt_device = mess_fb
            print(id_node)
            print(id_device)
            print(tt_device)
            hello= f'{id_node}{id_device}{tt_device}.'
            serial__.write(hello.encode())       
            print(hello.encode())            
                                 
    def serial_ports(self):
        """ Lists serial port names

            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        """
        # check đang dùng hệ điều hành nào
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            # kiểm tra các cổng com đang sẵn sàng
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        # danh sách các cổng com
        return result
    def add_com(self):
        # add danh sách cổng com vào box
        self.box_com.clear()                
        self.box_com.addItems(self.serial_ports())

    def set_serial_change(self):   
        global serial__             
        serial_com = self.box_com.currentText()    
        curr.execute("UPDATE CONFIG_GW SET THONGTIN = ? WHERE ATTRIBUTES = ?",[serial_com, "COM_PORT"])
        conn.commit() 
        self.set_serial()

    def set_serial(self):
        global serial__
        # chọn cổng com, tốc độ baud                             
        serial_baud = int(self.box_baud.currentText())
        # Đọc từ SQL Để xem đã có cổng com chưa
        curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'COM_PORT' ")
        if (len(curr.fetchall())>0): 
            thongtin_cfig=curr.execute("SELECT * FROM CONFIG_GW WHERE ATTRIBUTES = 'COM_PORT' ")
            serial_com = thongtin_cfig.fetchone()[1]
        else:
            serial_com = self.box_com.currentText()    
            curr.execute("INSERT INTO CONFIG_GW VALUES (?,?)",["COM_PORT",serial_com])
            conn.commit()    
        serial__.close()

        try:
            serial__=serial.Serial(serial_com, baudrate=serial_baud ,timeout=0.1)
        except:
            serial_com = self.box_com.currentText()    
            curr.execute("UPDATE CONFIG_GW SET THONGTIN = ? WHERE ATTRIBUTES = ?",[serial_com, "COM_PORT"])
            conn.commit()              
            serial__=serial.Serial(serial_com, baudrate=serial_baud ,timeout=0.1)
        print(serial__)

    def readData(self):
        # thread: lắng nghe uart
        if serial__.in_waiting >0:
            data_recv = serial__.readline()
            data_recv = data_recv.decode('utf-8')
            print(data_recv)   
            lenght_data = str(len(data_recv[data_recv.find('*'):data_recv.find('#')]))
            print(lenght_data)   

            data = data_recv.split("@")
            print(data)
            print(id_gw)
            print(name_gw)
            if data[3] == lenght_data:
                print("đúng độ dài")
            else:
                print("sai.y/c gửi lại")

            #C_F == config.
            # if data.find('C_F') > 0:
            #     self.thongtincauhinhnode(data)
            # # S_S == dữ liệu cảm biến.
            # elif data.find('S_S') > 0:
            #     self.uploadDataSensor(data) 
            # # D_V == trạng thái thiết bị on off.
            # elif data.find('D_V') > 0:
            #     self.uploadDataSensor(data)                 
            # # R_Q yêu cầu request, đồng bộ dữ liệu từ firebase.                
            # elif data.find('R_Q'):             
            #     pass  
  

    def read_interval(self):
        # thread
        self.timer = QtCore.QTimer()
        self.timer.setInterval(100)
        try:
            self.timer.timeout.connect(self.readData)
        except:
            print("readData error")
        self.timer.start()
    def senddata(self, tt):   
        if (tt==1):
            hello= 'on1123456789012345678901234567891' + '.'
        else:
            hello='off1234567890123456789012345678901' + '.'
        serial__.write(hello.encode())       
        print(hello.encode())
      
    def uploadDataSensor(self, data):
        print("up load sensor")
        print(data)
        # idnode = (data[1])
        # data = (data[data.find('LENGHT')+6:data.find('LENGHT')+8])
        # self.lab_hoagle.setText("TEMP: " + data)

        # print(idnode)
        # if idnode == "1":
        #     db.child(name_gw).child('phongngu1').update({'nhietdo':data})
        # elif idnode == "2":
        #     db.child(name_gw).child('phongngu2').update({'nhietdo':data})
        # elif idnode == "3":
        #     db.child(name_gw).child('phongngu1').update({'nhietdo':data})
        # elif idnode == "4":
        #     db.child(name_gw).child('phongngu2').update({'nhietdo':data})     
        # else:
        #     db.child(name_gw).child('phongkhach').update({'nhietdo':data})                 
    def thongtincauhinhnode(self,data):
        # tách thông tin cấu hình node
        # xử lý, update firebase
        print("xu ly node moi")
        print(f'data nhận được là :{data}')
        idnode_moi = data[1:data.find('C_F')]

        # THIẾT BỊ
        devices = data[data.find('ID_')+3:data.find('*')]
        print (idnode_moi + ":thietbi:" + devices)
        # xem đã có node đấy chưa.
        curr.execute("SELECT * FROM DATA_NODE WHERE ID_NODE = ? ", [idnode_moi] )
        if (len(curr.fetchall())>0): 
            curr.execute("DELETE FROM DATA_NODE WHERE ID_NODE = ?",[idnode_moi])
            # name_gw = thongtin_cfig.fetchone()[1]
        phanloai = "thietbi"
        db.child(name_gw).child(idnode_moi).set({'node':idnode_moi})          
        for i in devices:
            db.child(name_gw).child(idnode_moi).update({f'thietbi{i}':0}) 
            curr.execute("INSERT INTO DATA_NODE VALUES (?,?,?,?,?)",[idnode_moi,idnode_moi,phanloai,i,i])  
        conn.commit() 

        # CẢM BIẾN
        cambiens = data[data.find('*')+1:data.find('@')]
        print (idnode_moi + ":cambien:" + cambiens)
        phanloai = "cambien"       
        for i in cambiens:
            db.child(name_gw).child(idnode_moi).update({f'cambien{i}':0}) 
            curr.execute("INSERT INTO DATA_NODE VALUES (?,?,?,?,?)",[idnode_moi,idnode_moi,phanloai,i,i])  
        conn.commit()      


        hello=f'{name_gw}C_F:DONE' + '.'
        serial__.write(hello.encode())       
        print(hello.encode())           
        # DATA_NODE(ID_NODE char[20], NAME_ID_NODE char[20], PHANLOAI CHAR[20], ID_THIETBI CHAR[20], NAME_THIETBI CHAR[20]                  

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(550, 315)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.lab_hoagle = QtWidgets.QLabel(self.centralwidget)
        self.lab_hoagle.setGeometry(QtCore.QRect(140, 140, 240, 41))
        font = QtGui.QFont()
        font.setPointSize(20)
        self.lab_hoagle.setFont(font)
        self.lab_hoagle.setObjectName("lab_hoagle")
        self.butt_ok = QtWidgets.QPushButton(self.centralwidget)
        self.butt_ok.setGeometry(QtCore.QRect(250, 210, 75, 23))
        self.butt_ok.setObjectName("butt_ok")
        self.box_com = QtWidgets.QComboBox(self.centralwidget)
        self.box_com.setGeometry(QtCore.QRect(60, 40, 151, 31))
        self.box_com.setObjectName("box_com")
        self.box_baud = QtWidgets.QComboBox(self.centralwidget)
        self.box_baud.setGeometry(QtCore.QRect(240, 40, 151, 31))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.box_baud.setFont(font)
        self.box_baud.setObjectName("box_baud")
        self.box_baud.addItems(["1200", "2400", "4800", "9600", "14400", "19200", "38400", "57600", "115200", "128000"])
        self.lab_com = QtWidgets.QLabel(self.centralwidget)
        self.lab_com.setGeometry(QtCore.QRect(90, 0, 151, 41))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.lab_com.setFont(font)
        self.lab_com.setObjectName("lab_com")
        self.lab_baud = QtWidgets.QLabel(self.centralwidget)
        self.lab_baud.setGeometry(QtCore.QRect(270, 0, 151, 41))        
        font = QtGui.QFont()
        font.setPointSize(14)
        self.lab_baud.setFont(font)
        self.lab_baud.setObjectName("lab_baud")
        # self.butt_setup = QtWidgets.QPushButton(self.centralwidget)
        # self.butt_setup.setGeometry(QtCore.QRect(440, 40, 75, 31))
        # self.butt_setup.setObjectName("butt_setup")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 550, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.add_com()
        # self.butt_setup.clicked.connect(self.add_com)
        self.set_serial()
        self.box_com.currentIndexChanged.connect(self.set_serial_change)
        self.box_baud.currentIndexChanged.connect(self.set_serial_change)
        self.butt_ok.clicked.connect(self.senddata)
        t1 = Thread(target = self.read_interval())
        t1.start()
        db.child(name_gw).stream(self.stream_handler) 
        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.lab_hoagle.setText(_translate("MainWindow", "HoangLe"))
        self.butt_ok.setText(_translate("MainWindow", "OKAY"))
        self.lab_com.setText(_translate("MainWindow", "CỔNG COM"))
        self.lab_baud.setText(_translate("MainWindow", "BAUDRATE"))
        # self.butt_setup.setText(_translate("MainWindow", "SETUP"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

