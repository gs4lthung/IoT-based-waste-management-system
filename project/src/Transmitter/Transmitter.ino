#include <SPI.h>
#include <LoRa.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SENSOR_PIN D0 // GPIO pin connected to D0 of TCRT5000
#define LORA_SS_PIN D8
#define LORA_RST_PIN D4
#define LORA_DI0_PIN D1

char auth[] = "szH8X2Z-JgyoMdlmsjsPznAW-A6xerNK";
char ssid[] = "IZY coffee";
char pass[] = "12345678";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections!");
    while (1);
  }
  Serial.println("LoRa init successful.");
}

void loop() {
  int sensorValue = digitalRead(SENSOR_PIN); // Read the sensor value

  String trashStatus;
  if (sensorValue == 1) {
    trashStatus = "Trash bin IS NOT FULL";
    Blynk.virtualWrite(V0, 0); // Update Blynk Switch to "IS NOT FULL"
  } else {
    trashStatus = "Trash bin IS FULL";
    Blynk.virtualWrite(V0, 1); // Update Blynk Switch to "IS FULL"
  }
  // Convert integer value to bytes
  byte payload[sizeof(int)];
  memcpy(payload, &sensorValue, sizeof(int));
  
  LoRa.beginPacket();
  LoRa.write(payload, sizeof(int));         
  LoRa.endPacket();
  Serial.println(trashStatus+" --> Sent: " + sensorValue);

  delay(3000);
  Blynk.run();
}
