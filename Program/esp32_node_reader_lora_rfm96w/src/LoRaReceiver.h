#ifndef LORA_RECEIVER_H
#define LORA_RECEIVER_H

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// Konfigurasi LoRa
#define SS_PIN 5
#define RST_PIN 14
#define DIO0_PIN 2
#define RF95_FREQ 915E6
#define LED_INDICATOR 33

class LoRaReceiver
{
public:
      // Constructor
      LoRaReceiver(uint8_t ssPin = SS_PIN, uint8_t rstPin = RST_PIN, uint8_t dio0Pin = DIO0_PIN);

      // Fungsi untuk memulai LoRa
      void initLoRa();

      // Fungsi untuk menerima pesan LoRa
      bool receiveLoRaMessage(char *receivedMessage, size_t maxLength);

      // Fungsi untuk mengubah status indicator LED
      void setIndicatorState(bool state);

      // Fungsi untuk mengirim ACK
      void sendAck(const char *message);

private:
      uint8_t _ssPin;
      uint8_t _rstPin;
      uint8_t _dio0Pin;
};

#endif
