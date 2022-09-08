/*
 * Project mvmf2022-workshop
 * Description:
 * Author: Matteo Campinoti
 * Date: 2022-09-06
 */

#include "Particle.h"
#include "variables.h"
#include "light.h"

#define SENSOR_GL5528_PIN A0

double light = 0;
uint16_t lightRaw = 0;

void setup() {
  Particle.variable("version", VERSION);
  Particle.variable("light", light);
  Particle.variable("lightRaw", lightRaw);
}

void loop() {
  lightRaw = getLight(SENSOR_GL5528_PIN);
  int lightNew = lightRaw;
  if (lightNew >= 2048) lightNew = 2048;
  light = ((double) (lightNew)) / 2048;
  delay(500);
}
