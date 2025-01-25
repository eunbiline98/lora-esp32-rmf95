#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>
#include "LoRaHandler.h"

//========= Konfigurasi WiFi dan MQTT ============
const char *SSID = "xxxxxx";
const char *PASS = "xxxxxx";
const char *MQTT_SERVER = "xxxxxx";
const char *MQTT_RELAY = "xxxxxx";
const char *MQTT_NODES = "xxxxxx";
const char *MQTT_STATUS = "xxxxxx";
const char *WILL_MESSAGE = "xxxxxx";
const char *MQTT_CLIENT_ID = "xxxxxx";
const char *MQTT_USERNAME = "xxxxxx";
const char *MQTT_PASSWORD = "xxxxxx";

WiFiClient espClient;
MQTTClient client;
LoRaHandler loraHandler; // Instance dari LoRaHandler

unsigned long previousMillis = 0;
const unsigned long interval = 5000;
String pumpState = "";

// Fungsi koneksi WiFi
void setup_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }
  Serial.println("WiFi Connected.");
}

// Fungsi koneksi MQTT
void connectToMqtt()
{
  while (!client.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
  {
    delay(1000);
  }
  client.subscribe(MQTT_RELAY);
  client.publish(MQTT_STATUS, "Online", true, 1);
}

// Callback untuk pesan MQTT
void messageReceived(String &topic, String &payload)
{
  if (topic.equals(MQTT_RELAY))
  {
    if (payload.equalsIgnoreCase("ON") || payload.equalsIgnoreCase("OFF"))
    {
      pumpState = payload;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  client.begin(MQTT_SERVER, 1883, espClient);
  client.setWill(MQTT_STATUS, WILL_MESSAGE, true, 1);
  connectToMqtt();
  client.onMessage(messageReceived);

  if (!loraHandler.setupLoRa())
  {
    while (1)
      ; // Jika LoRa gagal, berhenti di sini
  }
}

void loop()
{
  if (!client.connected())
  {
    connectToMqtt();
  }
  client.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    loraHandler.sendMessage(pumpState);
  }

  String receivedMessage;
  if (loraHandler.receiveMessage(receivedMessage))
  {
    if (client.publish(MQTT_NODES, receivedMessage.c_str()))
    {
      Serial.println("Pesan LoRa dikirim ke MQTT!");
    }
  }
}
