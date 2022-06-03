// Please insert your motor encoder output pulse per rotation
int ENCODEROUTPUT = 11;
int HALLSEN_A = 5; 
// Motor AD connections 
int enA = 10;
int in1 = A1;
int in2 = A0;

volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
int motorPwm = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial with 9600 baudrate
  pinMode(HALLSEN_A, INPUT_PULLUP); // Set hall sensor A as input pullup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);
  Serial.print("\n\n");
  Serial.println("Measuring DC Motor's RPM");

}

void loop()
{
  encoderValue = 0;
  previousMillis = millis();

  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (motorPwm <= 0 || motorPwm < 250) {
      motorPwm += 50;
      analogWrite(enA, motorPwm);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    else if (motorPwm >= 250) {
      motorPwm -= 50;
      analogWrite(enA, motorPwm);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
    if (motorPwm > 0 || rpm > 0) {
      Serial.print(motorPwm);
      Serial.print('\t');
      Serial.print(encoderValue);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }  
    encoderValue = 0;
  }
}

void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}
