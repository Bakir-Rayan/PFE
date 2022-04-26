from time import sleep
import serial
import struct
ser = serial.Serial('COM6', 9600) 

while True:
    ser.write(struct.pack('BBB',1,1,255,12,12))
    sleep(.5)