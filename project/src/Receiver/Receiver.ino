#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

#define LORA_SS_PIN 10      // LoRa SS pin
#define LORA_RST_PIN 9      // LoRa RST pin
#define LORA_DI0_PIN 2      // LoRa DIO0 pin

Servo myservo;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa init successful.");
  LoRa.setTxPower(20);
  LoRa.receive();
  myservo.attach(3); // Set the servo pin
}

void loop() {
  if (LoRa.parsePacket()) {
    if (LoRa.available() >= sizeof(int)) { // Ensure enough bytes are available for an int
      int receivedValue = 0;

      // Read bytes into receivedValue
      LoRa.readBytes((uint8_t *)&receivedValue, sizeof(int));

      Serial.print("Received value: ");
      Serial.println(receivedValue);

      // Your servo control based on the received integer value
      // Example: Rotate the servo based on the received value
      // Adjust these conditions and servo control based on your specific needs
      if (receivedValue == 0) {
        myservo.write(0); // Rotate servo to position 0
        delay(1000); // Adjust delay as needed
      } else if (receivedValue == 1) {
        myservo.write(90); // Rotate servo to position 90
        delay(1000); // Adjust delay as needed
      }
    } else {
      Serial.println("Not enough bytes available for an int");
    }
  }
  delay(1000); // Adjust delay as needed
}
