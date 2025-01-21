# Control Pompa dengan LoRa (RFM95)

Proyek ini adalah implementasi sistem kontrol pompa menggunakan modul **LoRa RFM95**. Sistem terdiri dari dua modul utama: **Sender (Transmitter)** dan **Receiver**, dengan komunikasi melalui MQTT dan LoRa.

## Fitur Utama
- **Sender (Transmitter):**
  - Terhubung ke internet melalui Wi-Fi menggunakan ESP32.
  - Berkomunikasi dengan MQTT broker untuk menerima perintah.
  - Mengirimkan pesan ke Receiver melalui LoRa untuk mengontrol pompa/lampu.
- **Receiver:**
  - Menerima pesan dari Sender melalui LoRa.
  - Menyalakan atau mematikan pompa/lampu berdasarkan instruksi.

## Arsitektur Sistem
1. **MQTT Broker:**
   - Menyediakan komunikasi perintah menggunakan protokol MQTT.
2. **Sender (Transmitter):**
   - Mendengarkan perintah MQTT dengan topik tertentu.
   - Mengirimkan pesan melalui LoRa ke modul Receiver.
3. **Receiver:**
   - Menerima pesan dari Sender melalui LoRa.
   - Mengontrol pompa atau lampu berdasarkan pesan yang diterima.

## Hardware yang Dibutuhkan
1. **Sender (Transmitter):**
   - ESP32
   - Modul LoRa RFM95
   - Wi-Fi
2. **Receiver:**
   - ESP32 atau mikrokontroler lain dengan modul LoRa RFM95
   - Relay atau LED sebagai simulasi pompa

## Software yang Digunakan
- **Platform:** Arduino IDE atau PlatformIO
- **Library yang Dibutuhkan:**
  - [LoRa Library](https://github.com/sandeepmistry/arduino-LoRa)
  - [MQTT](https://github.com/256dpi/arduino-mqtt/tree/master) untuk MQTT
- **MQTT Broker:** Mosquitto atau alternatif lain

## Cara Kerja
1. MQTT broker menerima perintah dalam format berikut:
   - **ON:** Menyalakan pompa/lampu.
   - **OFF:** Mematikan pompa/lampu.
2. Modul Sender membaca perintah dari MQTT broker.
3. Sender mengirimkan pesan melalui LoRa ke Receiver.
4. Receiver menerima pesan dari Sender dan mengontrol pompa/lampu sesuai perintah.

## Instalasi
### 1. Konfigurasi Hardware
- Sambungkan ESP32 dengan modul LoRa RFM95 sesuai skema wiring berikut:
  - **Sender dan Receiver Pinout:**
    - **NSS (SS)** → Pin **D5**
    - **SCK** → Pin **D18**
    - **MISO** → Pin **D19**
    - **MOSI** → Pin **D23**
    - **RST** → Pin **D14**
    - **DIO0** → Pin **D2**

- Hubungkan modul Receiver ke relay atau LED sebagai output.


