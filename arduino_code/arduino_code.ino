#include <Servo.h>

int servoPin = 9;
int servoPin2 = 9;
Servo servo;
Servo servo2;

// serial control //
int val[5];

// Motor AD connections //
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor AG connections //
int enB = 3;
int in3 = 5;
int in4 = 4;
// Motor DD connections //
int enC = 9;
int in5 = 8;
int in6 = 7;
// Motor DG connections //
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

// need some changes //
void loop() {

  //val = Serial.read(); ** change it to table ** // done
  if(Serial.available()) {
    for (int i = 0; i < 5; i++) {
      val[i] = Serial.read();
    }    
  }
  switch (val[0]) {
  case 1:
    For_Backward(val[2], val[1]);
  case 2:
    LeftRight(val[2], val[1]);
  case 3:
    LeftDiagonal(val[2], val[1]);
  case 4:
    RightDiagonal(val[2], val[1]);
  case 5:
    Rotation(val[2], val[1]);
  case 6:
    Curve(val[2], val[1]);
  case 7:
    Stop();
}  
  /* servo control */
  servo.write(val[3]);
  servo2.write(val[4]);
  
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