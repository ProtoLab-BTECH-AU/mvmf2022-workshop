#pragma once

int getLight(uint8_t pin)
{
  int value = 0;
  for (char i = 0; i < 32; i++) value += analogRead(pin);

  value >>= 5; // divide by 2^5 = 32

  return value;
}
