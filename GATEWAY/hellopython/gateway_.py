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
# from firebase import firebase
global serial__ 
serial__=serial.Serial()


firebaseConfig = {
  'apiKey': "AIzaSyAEqi81NFMPBJGxWRy7QtQv961efPzL9LA",
  'authDomain': "hellodatn.firebaseapp.com",
  'databaseURL': "https://hellodatn-default-rtdb.asia-southeast1.firebasedatabase.app",
  'projectId': "hellodatn",
  'storageBucket': "hellodatn.appspot.com",
  'messagingSenderId': "559705579450",
  'appId': "1:559705579450:web:3421e5377912259256c783",
  'measurementId': "G-YK901S5FXQ"
};
# firebase = pyrebase.initialize_app(firebaseConfig)
# db=firebase.database()
# data={"name":"Hoàng", 'age':22, 'addr': 'Ha Tinh'}
# db.push(data)
# db.child('infor').set(data)
# db.child('infor').set({'addr':'binh duong'})

firebase = pyrebase.initialize_app(firebaseConfig)
db = firebase.database()

class Ui_MainWindow(object):

    def stream_handler(self, message):
        print(message["event"]) # put
        print("a")
        print(message["path"]) # /-K7yGTTEp7O549EzTYtI
        print("b")
        print(message["data"]) # {'title': 'Pyrebase', "body": "etc..."}
        # a=message["data"]
        # print (a['phongkhach']['nhietdo'] )
        print('hihi')
        self.senddata(message["data"])
    def serial_ports(self):
        """ Lists serial port names

            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        """
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
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result
    def add_com(self):
        self.box_com.clear()
        self.box_com.addItems(self.serial_ports())
        
    def set_serial(self):
        serial_com = self.box_com.currentText()
        serial_baud = int(self.box_baud.currentText())

        global serial__
        serial__.close()
        serial__=serial.Serial(serial_com, baudrate=serial_baud ,timeout=0.1)

    def readData(self):
        if serial__.in_waiting >0:
            data = serial__.readline()
            data = data.decode('utf-8')
            print(data)   
            data = (data[data.find('LENGHT')+6:data.find('LENGHT')+8])
            self.lab_hoagle.setText("TEMP: " + data)
            db.child('nhacuahoang/phongkhach').update({'nhietdo':data})

    def read_interval(self):
        self.timer = QtCore.QTimer()
        self.timer.setInterval(100)
        try:
            self.timer.timeout.connect(self.readData)
        except:
            print("readData error")
        self.timer.start()
    def senddata(self, tt):   
        if (tt==1):
            hello= 'on' + '.'
        else:
            hello='off' + '.'
        serial__.write(hello.encode())       
        print(hello.encode())
        # print( firebase.get('phòng 1','nhiệt độ'))
        # result = firebase.get('/phòng 1', None)
        # print(result)


    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(550, 315)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.lab_hoagle = QtWidgets.QLabel(self.centralwidget)
        self.lab_hoagle.setGeometry(QtCore.QRect(230, 140, 121, 41))
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
        self.box_com.currentIndexChanged.connect(self.set_serial)
        self.box_baud.currentIndexChanged.connect(self.set_serial)
        self.butt_ok.clicked.connect(self.senddata)
        t1 = Thread(target = self.read_interval())
        t1.start()
        my_stream = db.child("nhacuahoang").child("phongkhach").child("den").stream(self.stream_handler) 
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
