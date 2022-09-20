/*
 * Project mvmf2022-workshop
 * Description:
 * Author: Matteo Campinoti
 * Date: 2022-09-06
 */

#include "Particle.h"
#include "math.h"
#include "variables.h"

#ifdef SENSOR_ADXL345
#include "Wire.h"
#include "ADXL345.h"

ADXL345 adxl;
double acceleration = 1.0;
long wasTapped = 0;
#endif

#ifdef SENSOR_GL5528
#include "light.h"
#define SENSOR_GL5528_PIN A0
double light = 0;
int lightRaw = 0;
int lightThreshold = 2048;

int setLightThreshold(String newThreshold)
{
  for (unsigned int i = 0; i < newThreshold.length(); i++)
  {
    if (newThreshold[i] < 48 || newThreshold[i] > 57)
    {
      return -1;
    }
  }

  if (newThreshold.toInt() <= 0)
    return -1;

  lightThreshold = newThreshold.toInt();
  return lightThreshold;
}
#endif

unsigned int loopCounter = 0;

void setup()
{
#ifdef SENSOR_ADXL345
  Wire.begin();

  adxl.powerOn();
  adxl.setActivityThreshold(75);   // 62.5mg per increment
  adxl.setInactivityThreshold(75); // 62.5mg per increment
  adxl.setTimeInactivity(10);      // how many seconds of no activity is inactive?

  // look of activity movement on this axes - 1 == on; 0 == off
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  // look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);

  // look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(1);
  adxl.setTapDetectionOnY(1);
  adxl.setTapDetectionOnZ(1);

  // set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50);     // 62.5mg per increment
  adxl.setTapDuration(15);      // 625us per increment
  adxl.setDoubleTapLatency(80); // 1.25ms per increment
  adxl.setDoubleTapWindow(200); // 1.25ms per increment

  // set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

  // setting all interrupts to take place on int pin 1
  // I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);

  // register interrupt actions - 1 == on; 0 == off
  adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);

  Particle.variable("wasTapped", wasTapped);
  Particle.variable("acceleration", acceleration);
#endif

#ifdef SENSOR_GL5528
  Particle.variable("light", light);
  Particle.variable("lightRaw", lightRaw);
  Particle.variable("lightThreshold", lightThreshold);
  Particle.function("setLightThreshold", setLightThreshold);
#endif

  Particle.variable("version", VERSION);
  Particle.publish("version", VERSION);
}

void loop()
{
#ifdef SENSOR_ADXL345
  if (Time.now() - wasTapped >= 5)
  {
    wasTapped = 0;
  }

  double accelerationArray[3];
  adxl.getAcceleration(accelerationArray);

  double newAcceleration = sqrt(pow(accelerationArray[0], 2) + pow(accelerationArray[1], 2) + pow(accelerationArray[2], 2));

  if (abs(abs(newAcceleration) - abs(acceleration)) > 0.5)
  {
    wasTapped = Time.now();
  }

  acceleration = newAcceleration;
#endif

#ifdef SENSOR_GL5528
  lightRaw = getLight(SENSOR_GL5528_PIN);
  int lightNew = lightRaw;
  if (lightNew >= lightThreshold)
  {
    lightNew = lightThreshold;
  }
  light = ((double)(lightNew)) / lightThreshold;
#endif

  loopCounter++;
  delay(1);
}
