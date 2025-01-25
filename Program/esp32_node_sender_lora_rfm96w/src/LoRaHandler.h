#ifndef LORA_HANDLER_H
#define LORA_HANDLER_H

#include <Arduino.h>
#include <LoRa.h>

// Konfigurasi LoRa
#define SS_PIN 5
#define RST_PIN 14
#define DIO0_PIN 2
#define RF95_FREQ 915E6

class LoRaHandler
{
public:
      LoRaHandler();
      bool setupLoRa();
      void sendMessage(const String &message);
      bool receiveMessage(String &receivedMessage);

private:
      void configureLoRa();
};

#endif // LORA_HANDLER_H
