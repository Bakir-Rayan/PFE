import numpy as np
import cv2 as cv
from utils import *
import requests

cap = cv.VideoCapture(-1)
cap.set(3, 160)
cap.set(4, 120)
path = None

detector = cv.QRCodeDetector()
data = None
pwm=25
runnnig=False
while True :
    ret, frame = cap.read()
    frame = frame[60:120, 0:160]
    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    
    if path is None:
        try:
            path = str(requests.get('http://127.0.0.1:5000/test').content.decode("utf-8"))
        except:
            print("no path found on the server")

    if path == "yellow":
        contours, mask = yellow_mask(hsv)
        if contours:
            running = True
        else:
            running = False
            data = read_qr(detector, frame)
    elif path == "blue":
        contours, mask = blue_mask(hsv)
        if contours:
            running = True
        else:
            running = False
            data = read_qr(detector, frame)
    

    if running and (data is None):
        frame = get_contours(contours, frame, pwm)
    else:
        stop()
        if data == "yellow_zone":
            path = "yellow"
        elif data == "blue_zone":
            path = "blue"
        elif data == "start":
            path = None
            stop()
    
    cv.imshow('frame',frame)
    if cv.waitKey(1) & 0xFF == ord('q'):
        stop()
        gpio_cleanup()
        break
