#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6bP4FNpNI"
#define BLYNK_TEMPLATE_NAME "PROJECT"
#define BLYNK_AUTH_TOKEN "BvH3H3framvDOR6LVOmWDs9oAELIIZ9D"
#include <LoRa.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>
#include <NTPClient.h>
#include <TimeLib.h>

#define LORA_SS_PIN D8
#define LORA_RST_PIN D4
#define LORA_DI0_PIN D1
#define CLOSE_DISTANCE 10

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "..."; // your wifi name
char pass[] = "..."; // passwifi
int v0 = 0;          // Status garbage
// OFF
int v1 = 0; // LOCK

// Lock
BLYNK_WRITE(V0)
{
  v0 = param.asInt();
}

BLYNK_WRITE(V1)
{
  v1 = param.asInt();
}

// Trans
void commonSetup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  while (!Serial)
    ;

  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
  if (!LoRa.begin(433E6))
  {
    Serial.println("LoRa init failed. Check your connections!");
    while (1)
      ;
  }
  else
  {
    Serial.println("LoRa init successful.");
    LoRa.setTxPower(22);
  }
}

void sendToBlynk(int value1, int value2)
{
  Blynk.virtualWrite(V2, value1);
  Blynk.virtualWrite(V3, value2);
  //  Blynk.virtualWrite(V4, value3);
}

void setup()
{
  // Mode transmitter
  if (v0 == 0)
  {
    commonSetup();
  }
  // Mode receiver
  else
  {
    Serial.println("\n>>Receiver");
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    while (!Serial)
      ;

    LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
    if (!LoRa.begin(433E6))
    {
      Serial.println("LoRa init failed. Check your connections!");
      while (1)
        ;
    }
    else
    {
      Serial.println("LoRa init successful.");
      LoRa.setTxPower(20);
      LoRa.receive();
    }
  }
}

void loop()
{
  Blynk.run();
  if (v0 == 0 && LoRa.beginPacket())
  {
    String dataToSend = String(v0) + ", " + String(v1);
    LoRa.println(dataToSend);
    LoRa.endPacket();
    Serial.println("Data sent from ESP8266: " + dataToSend);
    delay(1000);
  }
  // Receive data from LoRa module
  else if (v0 != 0 && LoRa.parsePacket())
  {
    String receivedData = "";
    while (LoRa.available())
    {
      receivedData += (char)LoRa.read();
    }
    char delimiter[] = ", ";
    char *token = strtok((char *)receivedData.c_str(), delimiter);

    String data1 = token; // Percentage_Garbage_FULL
    token = strtok(NULL, delimiter);
    String data2 = token; // IS_OPEN OR NOT
    token = strtok(NULL, delimiter);
    String data3 = token;
    int value1 = data1.toInt();
    int value2 = data2.toInt();
    //    int value3 = data3.toInt();
    Serial.println("Data receive >> ");
    if (value2 == 1)
    {
      Serial.println("Percentage: " + data1 + ", Garbage OPEN");
    }
    else
    {
      Serial.println("Percentage: " + data1 + ", Garbage NOT_OPEN");
    }

    sendToBlynk(value1, value2);
  }
  delay(1);
}