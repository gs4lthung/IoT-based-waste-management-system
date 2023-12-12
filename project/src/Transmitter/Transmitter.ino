#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN_1 7
#define ECHO_PIN_1 6
#define TRIGGER_PIN_2 5
#define ECHO_PIN_2 4
#define SERVO_PIN 3
#define LORA_SS_PIN 10
#define LORA_RST_PIN 9
#define LORA_DI0_PIN 2
#define CLOSE_DISTANCE 10

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2);
Servo myServo;

int binFullCount = 0;

void setup()
{
  Serial.begin(115200);

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
  myServo.attach(SERVO_PIN);
  if (!LoRa.begin(433E6))
  {
    Serial.println("LoRa init failed. Check your connections!");
    while (1)
      ;
  }
  Serial.println("LoRa init successful.");
}

void loop()
{
  int distance1 = sonar1.ping_cm();
  int distance2 = sonar2.ping_cm();

  bool isHumanNearby = false;
  if (distance1 <= CLOSE_DISTANCE)
  {
    isHumanNearby = true;
    myServo.write(90);
  }
  else
  {
    isHumanNearby = false;
    myServo.write(0);
  }

  float emptyDistance = 30.0;
  float fullDistance = 5.0;
  float currentDistance = distance2;
  float percentage = 100.0 - ((currentDistance - fullDistance) / (emptyDistance - fullDistance)) * 100.0;
  percentage = constrain(percentage, 0, 100);

  // Construct the data to send via LoRa
  String dataToSend = String(percentage) + ", " + String(isHumanNearby);

  // Send the data via LoRa
  LoRa.beginPacket();
  LoRa.print(dataToSend);
  LoRa.endPacket();

  // Print the sent data to the Serial Monitor
  Serial.println("Sent 1 & 2: " + dataToSend);

  delay(1000);
}