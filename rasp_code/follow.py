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
    
    data = read_qr(detector,frame)

    if data == "start/yellow":
        contours, mask = yellow_mask(hsv)
        frame, cx = get_contours(contours, frame)
        print(get_motor_func(cx))
    elif data == "start/red":
        contours, mask = red_mask(hsv)
        frame, cx = get_contours(contours, frame)
        print(get_motor_func(cx))
    elif data == "start/blue":
        contours, mask = blue_mask(hsv)
        frame, cx = get_contours(contours, frame)
        print(get_motor_func(cx))
    elif data == "YELLOW ZONE":
        print("yellow")
        sleep(2)
        print("sleep 2s")
        list_ = [1, 3,4]
        sendSize += link.tx_obj(list_)
        link.send(sendSize)
        print("sent")
        #contours, mask = yellow_mask(hsv)
        #frame, cx = get_contours(contours, frame)
        #print(get_motor_func(cx))
        
    elif data == "red zone":
        contours, mask = red_mask(hsv)
        frame, cx = get_contours(contours, frame)
        print(get_motor_func(cx))
    elif data == "blue zone":
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
