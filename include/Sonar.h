#pragma once

#ifndef SONAR_H
#define SONAR_H

#include <NewPing.h>

#define TRIG_PIN 24
#define ECHO_PIN 26
#define MAX_DISTANCE 200 // cm

static NewPing _sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

float getDistanceCM()
{
  delay(30);
  float distance = _sonar.ping_cm();
  if (distance == 0)
    distance = 400;
  return distance;
}

#endif // SONAR_H