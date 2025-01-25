#include <Arduino.h>
#include "LoRaReceiver.h"
#include "PumpControl.h"

// Variabel kontrol pump dan waktu
unsigned long previousMillis = 0;
const long interval = 150;
const long timeoutMillis = 5000;
unsigned long lastReceivedMillis = 0;
unsigned long pumpStartMillis = 0;          // Waktu mulai ketika pump dinyalakan
const long pumpOnDuration = 10 * 60 * 1000; // 10 menit dalam milidetik
bool pumpState = LOW;
bool isTimeout = false; // Status timeout

// Membuat objek LoRaReceiver dengan pin default
LoRaReceiver loRaReceiver;

// Fungsi setup
void setup()
{
      Serial.begin(115200);
      while (!Serial)
            ;

      // Inisialisasi LoRa dan Lampu
      loRaReceiver.initLoRa();
      initPump();
}

// Fungsi loop
void loop()
{
      char receivedMessage[256];
      unsigned long currentMillis = millis();

      if (loRaReceiver.receiveLoRaMessage(receivedMessage, sizeof(receivedMessage)))
      {
            Serial.print("Pesan diterima: ");
            Serial.println(receivedMessage);

            String receivedStr = String(receivedMessage);
            if (receivedStr.equalsIgnoreCase("on"))
            {
                  setPumpState(HIGH);
                  Serial.println("Pump dinyalakan!");
                  pumpState = HIGH;
                  pumpStartMillis = currentMillis; // Simpan waktu saat pump dihidupkan
            }
            else if (receivedStr.equalsIgnoreCase("off"))
            {
                  setPumpState(LOW);
                  Serial.println("Pump dimatikan!");
                  pumpState = LOW;
            }
            else
            {
                  Serial.println("Pesan tidak valid atau tidak dikenal!");
            }

            lastReceivedMillis = currentMillis;
            isTimeout = false;

            // Kirim ACK
            loRaReceiver.sendAck(receivedMessage);
      }

      // Timeout untuk koneksi LoRa
      if (currentMillis - lastReceivedMillis >= timeoutMillis && !isTimeout)
      {
            isTimeout = true;
            Serial.println("Koneksi LoRa putus!");
      }

      // Mengubah status lampu jika timeout
      if (isTimeout && currentMillis - previousMillis >= interval)
      {
            previousMillis = currentMillis;
            loRaReceiver.setIndicatorState(!digitalRead(LED_INDICATOR));
      }

      // Jika pump dalam keadaan HIGH dan sudah berjalan 10 menit, matikan pump
      if (pumpState == HIGH && currentMillis - pumpStartMillis >= pumpOnDuration)
      {
            setPumpState(LOW);
            pumpState = LOW;
            Serial.println("Pump dimatikan setelah 10 menit!");
      }
      else if (!isTimeout)
      {
            setPumpState(pumpState);
      }
}
