import cv2 as cv
import numpy as np
from utils import *
from time import sleep
from pySerialTransfer import pySerialTransfer as txfer

cap = cv.VideoCapture(0)
cap.set(3,160)
cap.set(4,120)
detector = cv.QRCodeDetector()
try:
    link = txfer.SerialTransfer('/dev/ttyACM0')
except:
    link = txfer.SerialTransfer('/dev/ttyACM1')
link.open()
while True:
    sendSize = 0
    ret, frame = cap.read()
    frame = frame[60:120, 0:160]
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)

    sendSize += link.tx_obj([7,0,0,180])
    link.send(sendSize)
    sleep(1)
    data = read_qr(detector,frame)
    if data is not None:
        sendSize = 0
        link.send([7,1,0,0])

        if data == "start/yellow":
            while True:
                sendSize = 0
                contours, mask = yellow_mask(hsv)
                frame, cx = get_contours(contours, frame)
                if cx is not None:
                    s = get_motor_func(cx)
                    sendSize += link.tx_obj(s)
                    link.send(sendSize)
                else:
                    break

        elif data == "start/red":
            while True:
                sendSize = 0
                contours, mask = red_mask(hsv)
                frame, cx = get_contours(contours, frame)
                if cx is not None:
                    s = get_motor_func(cx)
                    sendSize += link.tx_obj(s)
                    link.send(sendSize)
                else:
                    break

        elif data == "start/blue":
            while True:
                sendSize = 0
                contours, mask = blue_mask(hsv)
                frame, cx = get_contours(contours, frame)
                if cx is not None:
                    s = get_motor_func(cx)
                    sendSize += link.tx_obj(s)
                    link.send(sendSize)
                else:
                    break

        elif data == "YELLOW ZONE":
            while True:
                sendSize = 0
                print("yellow")
                sleep(2)
                print("sleep 2s")
                list_ = [1, 3, 4]
                sendSize += link.tx_obj(list_)
                link.send(sendSize)
                print("sent")
                #contours, mask = yellow_mask(hsv)
                #frame, cx = get_contours(contours, frame)
                #print(get_motor_func(cx))
            
        elif data == "RED ZONE":
            while True:
                sendSize = 0
                contours, mask = red_mask(hsv)
                frame, cx = get_contours(contours, frame)
                print(get_motor_func(cx))

        elif data == "BLUE ZONE":
            while True:
                sendSize = 0
                contours, mask = blue_mask(hsv)
                frame, cx = get_contours(contours, frame)
                print(get_motor_func(cx))
        else:
            pass
        
    cv.namedWindow("Frame",cv.WINDOW_NORMAL)
    cv.imshow("Frame",frame)
    if cv.waitKey(1) == ord('q'):
        break
    
cap.release()
cv.destroyAllWindows()
