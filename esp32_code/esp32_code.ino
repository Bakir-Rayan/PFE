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

int enco1 = 17; // right front engine
int enco2 = 5; // left front engine
int enco3 = 18; //  left rear engine
int enco4 = 19; // right rear engine


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
}

void loop() {
  if(myTransfer.available())
  {
    uint16_t recSize = 0;
    recSize = myTransfer.txObj(testStruct, recSize);
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
    }
    rpm1 = (float)(encoderValue1 / ENCODEROUTPUT);
    rpm2 = (float)(encoderValue2 / ENCODEROUTPUT);
    rpm3 = (float)(encoderValue3 / ENCODEROUTPUT);
    rpm4 = (float)(encoderValue4 / ENCODEROUTPUT);
  
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