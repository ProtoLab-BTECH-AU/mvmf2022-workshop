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

void setup() {
  Particle.variable("version", VERSION);
  Particle.variable("light", light);
}

void loop() {
  light = ((double) getLight(SENSOR_GL5528_PIN)) / 4095;
  delay(500);
}
