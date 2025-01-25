#include "PumpControl.h"

void initPump()
{
      pinMode(PUMP_PIN, OUTPUT);
      digitalWrite(PUMP_PIN, LOW);
}

void setPumpState(bool state)
{
      digitalWrite(PUMP_PIN, state);
}
