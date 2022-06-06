#include "SerialTransfer.h"

SerialTransfer myTransfer;

struct __attribute__((packed)) STRUCT {
  long z[3];
} testStruct;

volatile long encoderValue1 = 0;
volatile long encoderValue2 = 0;
volatile long encoderValue3 = 0;
volatile long encoderValue4 = 0;

int ENCODEROUTPUT = 11;
int rpm1 = 0;
int rpm2 = 0;
int rpm3 = 0;
int rpm4 = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int enco1 = 17;
int enco2 = 5;
int enco3 = 18;
int enco4 = 19;

// Motor AD connections //
int enA = 16;
int in1 = 4;
int in2 = 2;
// Motor AG connections //
int enB = 15;
int in3 = 32;
int in4 = 33;
// Motor DD connections //
int enC = 13;
int in5 = 12;
int in6 = 14;
// Motor DG connections //
int enD = 25;
int in7 = 27;
int in8 = 26;

void setup() {
  Serial.begin(115200);
  myTransfer.begin(Serial);

  pinMode(enco1, INPUT_PULLUP);
  pinMode(enco2, INPUT_PULLUP);
  pinMode(enco3, INPUT_PULLUP);
  pinMode(enco4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(enco1), updateEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(enco2), updateEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(enco3), updateEncoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(enco4), updateEncoder4, RISING);

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
    encoderValue1 = 0;
    encoderValue2 = 0;
    encoderValue3 = 0;
    encoderValue4 = 0;
    previousMillis = millis();    
  }
  int val=testStruct.z[2];

  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;    
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
    rpm1 = (float)(encoderValue1 * 60 / ENCODEROUTPUT);
    rpm2 = (float)(encoderValue2 * 60 / ENCODEROUTPUT);
    rpm3 = (float)(encoderValue3 * 60 / ENCODEROUTPUT);
    rpm4 = (float)(encoderValue4 * 60 / ENCODEROUTPUT);
    Serial.print(rpm);
    Serial.println(" RPM 1");
    Serial.print(rpm);
    Serial.println(" RPM 2");
    Serial.print(rpm);
    Serial.println(" RPM 3");
    Serial.print(rpm);
    Serial.println(" RPM 4");
    encoderValue1 = 0;
    encoderValue2 = 0;
    encoderValue3 = 0;
    encoderValue4 = 0;
  }    
}

void updateEncoder1() {
  encoderValue1++;
}
void updateEncoder2() {
  encoderValue2++;
}
void updateEncoder3() {
  encoderValue3++;
}
void updateEncoder4() {
  encoderValue4++;
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