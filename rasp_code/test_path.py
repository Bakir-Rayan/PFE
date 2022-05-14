#import the libraries
import cv2 as cv
import numpy as np

#read the image
img = cv.imread("test.jpg")

hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
#obtain the grayscale image of the original image
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

#set the bounds for the blue hue
lower_blue = np.array([90,100,50])
upper_blue = np.array([130,255,255])

lower_red = np.array([160,100,50])
upper_red = np.array([180,255,255])

lower_yellow = np.array([19,100,100])
upper_yellow = np.array([39,255,255])

#create a mask using the bounds set
mask_red = cv.inRange(hsv, lower_red, upper_red)
mask_blue =cv.inRange(hsv, lower_blue, upper_blue)
mask_yellow = cv.inRange(hsv, lower_yellow, upper_yellow)

#create an inverse of the mask
mask_red_inv = cv.bitwise_not(mask_red)
mask_blue_inv = cv.bitwise_not(mask_blue)
mask_yellow_inv = cv.bitwise_not(mask_yellow)

#Filter only the red colour from the original image using the mask(foreground)
res_red = cv.bitwise_and(img, img, mask=mask_red)
res_blue = cv.bitwise_and(img, img, mask=mask_blue)
res_yellow = cv.bitwise_and(img, img, mask=mask_yellow)

#Filter the regions containing colours other than red from the grayscale image(background)
background_red = cv.bitwise_and(gray, gray, mask = mask_red_inv)
background_blue = cv.bitwise_and(gray, gray, mask = mask_blue_inv)
background_yellow = cv.bitwise_and(gray, gray, mask = mask_yellow_inv)

#convert the one channelled grayscale background to a three channelled image
background_red = np.stack((background_red,)*3, axis=-1)
background_blue = np.stack((background_blue,)*3, axis=-1)
background_yellow = np.stack((background_yellow,)*3, axis=-1)

#add the foreground and the background
added_img_red = cv.add(res_red, background_red)
added_img_blue = cv.add(res_blue, background_blue)
added_img_yellow = cv.add(res_yellow, background_yellow)

cv.namedWindow("back red", cv.WINDOW_NORMAL)
cv.namedWindow("back blue", cv.WINDOW_NORMAL)
cv.namedWindow("back yellow", cv.WINDOW_NORMAL)
cv.namedWindow("mask_red_inv", cv.WINDOW_NORMAL)
cv.namedWindow("mask_blue_inv", cv.WINDOW_NORMAL)
cv.namedWindow("mask_yellow_inv", cv.WINDOW_NORMAL)
cv.namedWindow("added red", cv.WINDOW_NORMAL)
cv.namedWindow("added blue", cv.WINDOW_NORMAL)
cv.namedWindow("added yellow", cv.WINDOW_NORMAL)
cv.namedWindow("mask red", cv.WINDOW_NORMAL)
cv.namedWindow("mask blue", cv.WINDOW_NORMAL)
cv.namedWindow("mask yellow", cv.WINDOW_NORMAL)
cv.namedWindow("gray", cv.WINDOW_NORMAL)
cv.namedWindow("hsv", cv.WINDOW_NORMAL)
cv.namedWindow("res red", cv.WINDOW_NORMAL)
cv.namedWindow("res blue", cv.WINDOW_NORMAL)
cv.namedWindow("res yellow", cv.WINDOW_NORMAL)

#display the images
cv.imshow("back red", background_red)
cv.imshow("back blue", background_blue)
cv.imshow("back yellow", background_yellow)

cv.imshow("mask_red_inv", mask_red_inv)
cv.imshow("mask_blue_inv", mask_blue_inv)
cv.imshow("mask_yellow_inv", mask_yellow_inv)

cv.imshow("added red",added_img_red)
cv.imshow("added blue",added_img_blue)
cv.imshow("added yellow",added_img_yellow)

cv.imshow("mask red", mask_red)
cv.imshow("mask blue", mask_blue)
cv.imshow("mask yellow", mask_yellow)

cv.imshow("gray", gray)
cv.imshow("hsv", hsv)

cv.imshow("res red", res_red)
cv.imshow("res blue", res_blue)
cv.imshow("res yellow", res_yellow)

if cv.waitKey(0):
    cv.destroyAllWindows()
