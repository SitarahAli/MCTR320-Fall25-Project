/*
* 12-Servo Robot Dog - CALIBRATION MODE ONLY
* Uses PCA9685 servo driver board
* 
* This program moves each servo to 90 degrees one at a time
* so you can observe and record the angles needed for proper standing.
* 
* Servo Layout:
* Front Left Leg:  Servos 0 (shoulder), 1 (elbow), 2 (wrist)
* Front Right Leg: Servos 3 (shoulder), 4 (elbow), 5 (wrist)
* Back Left Leg:   Servos 6 (shoulder), 7 (elbow), 8 (wrist)
* Back Right Leg:  Servos 9 (shoulder), 10 (elbow), 11 (wrist)
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create servo driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo pulse length constants
#define SERVOMIN  150  // Min pulse length (adjust based on your servos)
#define SERVOMAX  600  // Max pulse length (adjust based on your servos)
#define SERVO_FREQ 50  // Servo frequency (50 Hz)

// Servo names for calibration printout
const char* servoNames[12] = {
  "Front Left Shoulder", "Front Left Elbow", "Front Left Wrist",
  "Front Right Shoulder", "Front Right Elbow", "Front Right Wrist",
  "Back Left Shoulder", "Back Left Elbow", "Back Left Wrist",
  "Back Right Shoulder", "Back Right Elbow", "Back Right Wrist"
};

void setup() {
  Serial.begin(9600);
  Serial.println("===== Robot Dog Calibration Mode =====\n");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);

  Serial.println("Each servo will move to 90 degrees one at a time.");
  Serial.println("Observe each position and note adjustments needed.\n");

  delay(2000);
  calibrateServos();
}

void calibrateServos()
{Serial.println("Starting calibration sequence...\n");
  Serial.println("Moving ALL servos to 90 degrees simultaneously...\n");

  delay(1000);

  setServo(0,90);
  setServo(3, 90);
  setServo(6,85); //shoulder 3 needs to be at 85 degrees
  setServo(9, 93);

  delay(1000);

  setServo(2,100);
  setServo(5, 80);
  setServo(8,100);
  setServo(11, 80);

  delay(1000);

  setServo(2,90);
  setServo(5, 90);
  setServo(8,90);
  setServo(11, 90);

  delay(1000);

  setServo(1,90);
  setServo(4, 90);
  setServo(7,90);
  setServo(10, 90);}

  // Convert angle (0-180) to pulse length
int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

// Set servo to specific angle
void setServo(uint8_t num, int angle) {
  angle = constrain(angle, 0, 180);
  int pulse = angleToPulse(angle);
  pwm.setPWM(num, 0, pulse);
}

void loop() {
  // Hold position after calibration
  walkSequence();
}


// Calibration routine
void walkSequence() {
  //1 and 3 (180 - values) are opposite of 2 and 4 (at values)

  delay(500);

  setServo(1,115);
  setServo(2,110);

  setServo(10,65);
  setServo(11,85);

  setServo(4,120);
  setServo(5,90);

  setServo(7,90);
  setServo(8,95);


  delay(500);

  setServo(4,65);
  setServo(5,90);

  setServo(7,115);
  setServo(8,110);

  setServo(1,90);
  setServo(2,90);

  setServo(10,90);
  setServo(11,95);


  Serial.println("All servos are now at 90 degrees.");
  Serial.println("\nServo positions:");
  for (int i = 0; i < 12; i++) {
    Serial.print("  Servo ");
    Serial.print(i);
    Serial.print(" (");
    Serial.print(servoNames[i]);
    Serial.println(") = 90 degrees");
  }

  Serial.println("\n***** CALIBRATION COMPLETE *****");
  Serial.println("All servos are now at 90 degrees.");
  Serial.println("\nNext steps:");
  Serial.println("1. Look at your robot's standing position");
  Serial.println("2. Note which servos need adjustment");
  Serial.println("3. Record the angles you need in this format:\n");

  Serial.println("int standPos[12] = {");
  Serial.println("  90, 90, 90,  // Front Left: shoulder, elbow, wrist");
  Serial.println("  90, 90, 90,  // Front Right: shoulder, elbow, wrist");
  Serial.println("  90, 90, 90,  // Back Left: shoulder, elbow, wrist");
  Serial.println("  90, 90, 90   // Back Right: shoulder, elbow, wrist");
  Serial.println("};");
  Serial.println("\n4. Use these values in your main robot dog program");
}
