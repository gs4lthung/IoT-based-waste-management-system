#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN 7     // SR04 Trigger pin
#define ECHO_PIN 6        // SR04 Echo pin
#define SERVO_PIN 3         // Servo pin

Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO_PIN); // Attach servo to pin
}

void loop() {
  int distance = sonar.ping_cm();
  delay(50);

  if (distance < 10) { // Adjust threshold distance as needed
    // If object is close, rotate the servo to position 0 degrees
    myservo.write(0);
    delay(1000); // Adjust delay as needed
  } else {
    // If object is farther away, rotate the servo to position 90 degrees
    myservo.write(90);
    delay(1000); // Adjust delay as needed
  }
}
