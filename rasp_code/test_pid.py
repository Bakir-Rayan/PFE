import PID
import time
import os.path
import random

targetPWM = 60
P = 1
I = 0.8
D = 0.5

pid = PID.PID(P, I, D)
pid.SetPoint = targetPWM
pid.setSampleTime(1)

cx=[]
for i in range(0,126):
    cx.append(60-i)
j=0
while j<=55:
    x=random.choice(cx)
    pid.update(x)
    targetPwm = pid.output
    
    if targetPwm > 100:
        targetPwm = 75
    if targetPwm < 0:
        targetPwm += 100
        targetPwm = abs(targetPwm)
    
    print(f"Target: {targetPWM} PWM | Current: {x} distance | PWM: {int(targetPwm)} %")
    time.sleep(0.5)
    j+=1