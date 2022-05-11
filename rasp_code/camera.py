import cv2
import numpy as np
 
cap = cv2.VideoCapture(0)
 
while(1):
    ret, frame = cap.read()
    # It converts the BGR color space of image to HSV color space
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
 
    cv2.imshow('frame', frame)

    
    if cv2.waitKey(1)== ord("q"):
        break
 
cv2.destroyAllWindows()
cap.release()