import cv2 as cv
import numpy as np


def red_mask(hsv):
    lower_red = np.array([160,100,50])
    upper_red = np.array([180,255,255])
    mask_red = cv.inRange(hsv, lower_red, upper_red)
    rett,thresh = cv.threshold(mask_red,50,255,cv.THRESH_BINARY)
    contours,hierarchy = cv.findContours(thresh.copy(), cv.RETR_CCOMP, cv.CHAIN_APPROX_NONE)
    return contours, mask_red
    
def blue_mask(hsv):
    lower_blue = np.array([90,100,50])
    upper_blue = np.array([130,255,255])
    mask_blue = cv.inRange(hsv, lower_blue, upper_blue)
    rett,thresh = cv.threshold(mask_blue,50,255,cv.THRESH_BINARY)
    contours,hierarchy = cv.findContours(thresh.copy(), cv.RETR_CCOMP, cv.CHAIN_APPROX_NONE)
    return contours, mask_blue

def yellow_mask(hsv):
    lower_yellow = np.array([19,100,100])
    upper_yellow = np.array([39,255,255])
    mask_yellow = cv.inRange(hsv, lower_yellow, upper_yellow)
    rett,thresh = cv.threshold(mask_yellow,50,255,cv.THRESH_BINARY)
    contours,hierarchy = cv.findContours(thresh.copy(), cv.RETR_CCOMP, cv.CHAIN_APPROX_NONE)
    return contours, mask_yellow

def get_contours(contours, frame):
    if len(contours) > 0:
        C=max(contours, key=cv.contourArea)
        M = cv.moments(C)
        if M["m00"] != 0:
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            cv.circle(frame, (cx,cy), 5, (255,255,255), -1)
        cv.drawContours(frame, C, -1, (0,255,0), 1)
    return frame, cx

def get_motor_func(cx):
    if cx >= 120:
        return [1,2,3]
    elif cx < 120 and cx > 50:
        return [4,5,6]
    elif cx <= 50:
        return [7,8,9]

def speed()
    pass

def read_qr(detector, img):
    detector = detector
    data, bbox, straight_qrcode = detector.detectAndDecode(img)
    if data:
        return data
    else:
        return None
