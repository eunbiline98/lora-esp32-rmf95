#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <Arduino.h>

// Pin untuk Pumpu
#define PUMP_PIN 25

// Fungsi untuk menginisialisasi Pumpu
void initPump();

// Fungsi untuk mengubah status Pumpu
void setPumpState(bool state);

#endif
