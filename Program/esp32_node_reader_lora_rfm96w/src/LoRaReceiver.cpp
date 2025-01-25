#include "LoRaReceiver.h"
#include <LoRa.h>

LoRaReceiver::LoRaReceiver(uint8_t ssPin, uint8_t rstPin, uint8_t dio0Pin)
    : _ssPin(ssPin), _rstPin(rstPin), _dio0Pin(dio0Pin) {}

void LoRaReceiver::initLoRa()
{
      pinMode(LED_INDICATOR, OUTPUT);
      LoRa.setPins(_ssPin, _rstPin, _dio0Pin);
      if (!LoRa.begin(RF95_FREQ))
      {
            Serial.println("Gagal memulai LoRa! Periksa wiring atau frekuensi.");
            while (1)
                  delay(100);
      }
      Serial.println("LoRa Initialized!");
}

bool LoRaReceiver::receiveLoRaMessage(char *receivedMessage, size_t maxLength)
{
      int packetSize = LoRa.parsePacket();
      if (packetSize)
      {
            int index = 0;
            while (LoRa.available() && index < maxLength - 1)
            {
                  receivedMessage[index++] = (char)LoRa.read();
            }
            receivedMessage[index] = '\0'; // Terminator null
            return true;
      }
      return false;
}

void LoRaReceiver::sendAck(const char *message)
{
      LoRa.beginPacket();
      delay(10); // Tunda sedikit sebelum mengirim
      LoRa.print("ACK: ");
      LoRa.print(message);
      int result = LoRa.endPacket();
      if (result == 1)
      {
            Serial.println("ACK terkirim!");
      }
      else
      {
            Serial.print("Gagal mengirim ACK! (error code: ");
            Serial.print(result);
            Serial.println(")");
      }
}

void LoRaReceiver::setIndicatorState(bool state)
{
      digitalWrite(LED_INDICATOR, state);
}
