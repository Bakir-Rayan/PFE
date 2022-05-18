#include <Servo.h>
#include "SerialTransfer.h"

SerialTransfer myTransfer;

int servoPin = 6;
Servo servo;

struct __attribute__((packed)) STRUCT {
  long val[4];
} command;

// Motor AD connections //
int enA = 9;
int in1 = A1;
int in2 = A0;
// Motor AG connections //
int enB = 3;
int in3 = 2;
int in4 = 4;
// Motor DD connections //
int enC = 11;
int in5 = 13;
int in6 = 12;
// Motor DG connections //
int enD = 10;
int in7 = 8;
int in8 = 7;

void setup() {

  Serial.begin(115200);
  myTransfer.begin(Serial);

  servo.attach(servoPin);

	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(enC, OUTPUT);
	pinMode(enD, OUTPUT);
	pinMode(in5, OUTPUT);
	pinMode(in6, OUTPUT);
	pinMode(in7, OUTPUT);
	pinMode(in8, OUTPUT);

	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
	digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, LOW);
}

// need some changes //
void loop() {

  //val = Serial.read(); ** change it to table ** // done
  if(myTransfer.available())
  {
    // use this variable to keep track of how many
    // bytes we've processed from the receive buffer
    uint16_t recSize = 0;
    recSize = myTransfer.rxObj(command, recSize);
  }
  switch (command.val[0]) {
    case 1:
      For_Backward(command.val[2], command.val[1]);
    case 2:
      LeftRight(command.val[2], command.val[1]);
    case 3:
      LeftDiagonal(command.val[2], command.val[1]);
    case 4:
      RightDiagonal(command.val[2], command.val[1]);
    case 5:
      Rotation(command.val[2], command.val[1]);
    case 6:
      Curve(command.val[2], command.val[1]);
    case 7:
      Stop();
  }  
  /* servo control */
  servo.write(command.val[3]);
}

// forward or backward //
void For_Backward(int speed, int direction)/* 1 */ {
  analogWrite(enA, speed);
	analogWrite(enB, speed);  
  analogWrite(enC, speed);
	analogWrite(enD, speed);

  // go forward
  if (direction==1) {
    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  }
  // go backward
  if (direction==0) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);      
  }
}

// left or right //
void LeftRight(int speed, int direction)/* 2 */ {
  analogWrite(enA, speed);
	analogWrite(enB, speed);  
  analogWrite(enC, speed);
	analogWrite(enD, speed);

  // go left
  if (direction==1) {
    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  }
  // go right
  if (direction==0) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);      
  }
}

// left diagonal "\" forward or backward //
void LeftDiagonal(int speed, int direction)/* 3 */ {
  analogWrite(enA, speed);
	analogWrite(enB, 0);  
  analogWrite(enC, 0);
	analogWrite(enD, speed);

  // go forward "\"
  if (direction==1) {
    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  }
  // go backward "\"
  if (direction==0) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);      
  }
}

// right diagonal "/" forward or backward //
void RightDiagonal(int speed, int direction)/* 4 */ {
  analogWrite(enA, 0);
	analogWrite(enB, speed);  
  analogWrite(enC, speed);
	analogWrite(enD, 0);

  // go forward "/"
  if (direction==1) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, LOW);
  }
  // go backward "/"
  if (direction==0) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);      
  }
}

// rotate 350° clockwise or anticlockwise
void Rotation(int speed, int direction)/* 5 */ {
  analogWrite(enA, speed);
	analogWrite(enB, speed);  
  analogWrite(enC, speed);
	analogWrite(enD, speed);

  // go clockwise
  if (direction==1) {
    // motor AD
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  }
  // go anticlockwise
  if (direction==0) {
    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);      
  }
}

// curve depend on the speed of the motors
void Curve(int speed, int direction)/* 6 */ {

  // go forward right 
  if (direction==1) {
    analogWrite(enA, speed/2);
    analogWrite(enB, speed);  
    analogWrite(enC, speed/2);
    analogWrite(enD, speed);

    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);
  }
  // go forward left
  if (direction==0) {
    analogWrite(enA, speed);
    analogWrite(enB, speed/2);  
    analogWrite(enC, speed);
    analogWrite(enD, speed/2);

    // motor AD
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // motor AG
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    // motor DD
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // motor DG
    digitalWrite(in7, HIGH);
    digitalWrite(in8, LOW);      
  }
}

// stop the robot
void Stop()/* 7 */ {
  analogWrite(enA, 0);
  analogWrite(enB, 0);  
  analogWrite(enC, 0);
  analogWrite(enD, 0);

  // motor AD
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // motor AG
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // motor DD
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  // motor DG
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}