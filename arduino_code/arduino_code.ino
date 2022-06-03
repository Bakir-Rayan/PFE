#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct __attribute__((packed)) STRUCT {
  long z[3];
} testStruct;

// Motor AD connections //
int enA = 10;
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
int enD = 6;
int in7 = 8;
int in8 = 7;

void setup() {
  Serial.begin(115200);
  myTransfer.begin(Serial);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enC, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  pinMode(enD, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);

  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

void loop() {
  if(myTransfer.available())
  {
    uint16_t recSize = 0;
    recSize = myTransfer.rxObj(testStruct, recSize);
  }
  int val=testStruct.z[2];

  switch (val) {
    case 1:
      For_Backward(testStruct.z[0], testStruct.z[1]);  
      break;  
    case 2:
      Rotation(testStruct.z[0], testStruct.z[1]);
      break;
    case 3:
      Curve(testStruct.z[0], testStruct.z[1]);
      break;
    case 4:
      Stop();
      break;
  }  
}

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

void Rotation(int speed, int direction)/* 2 */ {
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

void Curve(int speed, int direction)/* 3 */ {

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

void Stop()/* 4 */ {
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