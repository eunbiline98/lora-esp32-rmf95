#include "LoRaHandler.h"

LoRaHandler::LoRaHandler() {}

bool LoRaHandler::setupLoRa()
{
      LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);
      if (!LoRa.begin(RF95_FREQ))
      {
            Serial.println("Gagal memulai LoRa!");
            return false;
      }
      Serial.println("LoRa Initialized!");
      LoRa.setTxPower(23);
      return true;
}

void LoRaHandler::sendMessage(const String &message)
{
      LoRa.beginPacket();
      LoRa.print(message); // Kirim pesan
      LoRa.endPacket();
      Serial.println("Pesan terkirim: " + message);
}

bool LoRaHandler::receiveMessage(String &receivedMessage)
{
      int packetSize = LoRa.parsePacket();
      if (packetSize > 0)
      {
            receivedMessage = "";
            while (LoRa.available())
            {
                  receivedMessage += (char)LoRa.read();
            }
            Serial.println("Pesan diterima: " + receivedMessage);
            return true;
      }
      return false;
}
