#include <Servo.h>

int servoPin = 9;
int servoPin2 = 9;
Servo servo;
Servo servo2;
int angle = 0;  // servo position in degrees

// serial control
int val;

// Motor AD connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor AG connections
int enB = 3;
int in3 = 5;
int in4 = 4;
// Motor DD connections
int enC = 9;
int in5 = 8;
int in6 = 7;
// Motor DG connections
int enD = 3;
int in7 = 5;
int in8 = 4;

void setup() {

  Serial.begin(9600);

  servo.attach(servoPin);
  servo2.attach(servoPin2);

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


void loop() {
  if (Serial.available() > 0){
    val = Serial.read();
    Serial.write("\n");
    if(val==1){
      Serial.write("ON");
      }
    if(val==0){
      Serial.write("OFF");
      }
  }
}