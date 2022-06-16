import cv2 as cv
import numpy as np
import RPi.GPIO as GPIO  

# motor pins
# right front engine
enA = 23
in1 = 25
in2 = 24
# left front engine
enB = 21
in3 = 20
in4 = 16
# right rear engine
enC = 11
in5 = 5
in6 = 6
# left rear engine
enD = 26
in7 = 13
in8 = 19

# set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# set up motor pins
GPIO.setup(enA, GPIO.OUT)
GPIO.setup(in1,GPIO.OUT)
GPIO.setup(in2,GPIO.OUT)

GPIO.setup(enB, GPIO.OUT)
GPIO.setup(in3,GPIO.OUT)
GPIO.setup(in4,GPIO.OUT)

GPIO.setup(enC, GPIO.OUT)
GPIO.setup(in5,GPIO.OUT)
GPIO.setup(in6,GPIO.OUT)

GPIO.setup(enD, GPIO.OUT)
GPIO.setup(in7,GPIO.OUT)
GPIO.setup(in8,GPIO.OUT)

# set up motor PWM
PWM1=GPIO.PWM(enA,1000)
PWM2=GPIO.PWM(enB,1000)
PWM3=GPIO.PWM(enC,1000)
PWM4=GPIO.PWM(enD,1000)
    
def blue_mask(hsv):
    lower_blue = np.array([100,100,50])
    upper_blue = np.array([130,255,255])
    mask_blue = cv.inRange(hsv, lower_blue, upper_blue)
    rett,thresh = cv.threshold(mask_blue,50,255,cv.THRESH_BINARY + cv.THRESH_OTSU)
    contours,hierarchy = cv.findContours(thresh.copy(), cv.RETR_CCOMP, cv.CHAIN_APPROX_NONE)
    return contours, mask_blue

def yellow_mask(hsv):
    lower_yellow = np.array([19,100,100])
    upper_yellow = np.array([39,255,255])
    mask_yellow = cv.inRange(hsv, lower_yellow, upper_yellow)
    rett,thresh = cv.threshold(mask_yellow,30,255,cv.THRESH_BINARY)
    contours,hierarchy = cv.findContours(thresh.copy(), cv.RETR_CCOMP, cv.CHAIN_APPROX_NONE)
    return contours, mask_yellow

def get_contours(contours, frame, pwm):
    if len(contours) > 0:
        C=max(contours, key=cv.contourArea)
        M = cv.moments(C)
        if M["m00"] != 0:
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            cv.circle(frame, (cx,cy), 5, (255,255,255), -1)
            if cx >= 110:
                go_left(pwm)
            elif cx < 110 and cx > 50:
                go_forward(pwm)
            elif cx <= 50:
                go_right(pwm)
        cv.drawContours(frame, C, -1, (0,255,0), 1)
    return frame

def stop():
    PWM1.stop()
    PWM2.stop()
    PWM3.stop()
    PWM4.stop()

def gpio_cleanup():
    GPIO.cleanup()

def go_forward(pwm):
    print("go forward")
    PWM1.start(pwm)
    PWM2.start(pwm)
    PWM3.start(pwm)
    PWM4.start(pwm)
    GPIO.output(in1,GPIO.HIGH)
    GPIO.output(in2,GPIO.LOW)
    GPIO.output(in3,GPIO.HIGH)
    GPIO.output(in4,GPIO.LOW)
    GPIO.output(in5,GPIO.HIGH)
    GPIO.output(in6,GPIO.LOW)
    GPIO.output(in7,GPIO.HIGH)
    GPIO.output(in8,GPIO.LOW)

def go_left(pwm):
    print("go left")
    PWM1.start(pwm)
    PWM2.start(pwm)
    PWM3.start(pwm)
    PWM4.start(pwm)
    GPIO.output(in1,GPIO.HIGH)
    GPIO.output(in2,GPIO.LOW)
    GPIO.output(in3,GPIO.LOW)
    GPIO.output(in4,GPIO.HIGH)
    GPIO.output(in5,GPIO.HIGH)
    GPIO.output(in6,GPIO.LOW)
    GPIO.output(in7,GPIO.LOW)
    GPIO.output(in8,GPIO.HIGH)

def go_right(pwm):
    print("go right")
    PWM1.start(pwm)
    PWM2.start(pwm)
    PWM3.start(pwm)
    PWM4.start(pwm)
    GPIO.output(in1,GPIO.LOW)
    GPIO.output(in2,GPIO.HIGH)
    GPIO.output(in3,GPIO.HIGH)
    GPIO.output(in4,GPIO.LOW)
    GPIO.output(in5,GPIO.LOW)
    GPIO.output(in6,GPIO.HIGH)
    GPIO.output(in7,GPIO.HIGH)
    GPIO.output(in8,GPIO.LOW)

def read_qr(detector, img):
    detector = detector
    data, bbox, straight_qrcode = detector.detectAndDecode(img)
    if data:
        return data
    else:
        return None


