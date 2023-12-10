#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>
#include <NewPing.h>

#define LORA_SS_PIN 10      // LoRa SS pin
#define LORA_RST_PIN 9      // LoRa RST pin
#define LORA_DI0_PIN 2      // LoRa DIO0 pin
#define TRIGGER_PIN D5      // SR04 Trigger pin
#define ECHO_PIN D6         // SR04 Echo pin

Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN);

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
  // Nhận dữ liệu từ module LoRa
  if (LoRa.parsePacket()) {
    String receivedValue = "";

    while (LoRa.available()) {
      receivedValue += (char)LoRa.read();
    }
    Serial.println(receivedValue);
    if (receivedValue.equals("Trash bin IS NOT FULL")) {
      // Kiểm tra khoảng cách từ cảm biến siêu âm SR04
      int distance = sonar.ping_cm();
      delay(50);

      // Nếu khoảng cách nhỏ hơn giá trị ngưỡng (điều kiện để mở servo)
      if (distance < 10) { // Thay giá trị ngưỡng ở đây
        // Rotate the servo in one direction
        myservo.write(0);
        delay(1000); // Adjust delay as needed
      }
    } else if (receivedValue.equals("Trash bin IS FULL")) {
      // Rotate the servo in the other direction
      myservo.write(90);
      delay(1000); // Adjust delay as needed
    }
  }
  delay(1000);
}
