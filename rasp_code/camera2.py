import cv2
import numpy as np

cap = cv2.VideoCapture(0)
while True:
    ret, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
     
    lower_hsv = np.array([30, 70, 100])
    upper_hsv = np.array([90, 255, 255])
    
    mask = cv2.inRange(hsv, lower_hsv, upper_hsv)
     
    mask = cv2.bitwise_not(mask)
    #result = cv2.bitwise_and(frame, frame, mask = mask)
    
    #gray = cv2.cvtColor(result, cv2.COLOR_BGR2GRAY)
    #blur = cv2.GaussianBlur(result,(5,5),0)

    # Color thresholding
    ret,thresh = cv2.threshold(mask,60,255,cv2.THRESH_BINARY_INV)
    
    # Find the contours of the frame
    contours,hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # Find the biggest contour (if detected)
    for contour in contours:
        x,y,w,h = cv2.boundingRect(contour)
        img = cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
    
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()
