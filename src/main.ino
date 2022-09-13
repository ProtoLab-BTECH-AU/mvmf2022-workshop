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
int lightRaw = 0;
int lightThreshold = 2048;

int setLightThreshold(String newThreshold)
{
  try
  {
    lightThreshold = newThreshold.toInt();
    return lightThreshold;
  }
  catch (const std::exception &e)
  {
    return -1;
  }
}

void setup()
{
  Particle.variable("version", VERSION);
  Particle.variable("light", light);
  Particle.variable("lightRaw", lightRaw);
  Particle.variable("lightThreshold", lightThreshold);
  Particle.function("setLightThreshold", setLightThreshold);
}

void loop()
{
  lightRaw = getLight(SENSOR_GL5528_PIN);
  int lightNew = lightRaw;
  if (lightNew >= lightThreshold)
  {
    lightNew = lightThreshold;
  }
  light = ((double)(lightNew)) / lightThreshold;
  delay(500);
}
