#pragma once

#ifndef _STEPPERCONTROL_H_
#define _STEPPERCONTROL_H_

#include <Arduino.h>
#include <AccelStepper.h>

// Positive Value is up for vertical and right for horizonal

#define EN_PIN A3

#define VER_STEP 8
#define VER_DIR 9
#define HOR_STEP 10
#define HOR_DIR 11

#define SWITCH_VER 12
#define SWITCH_HOR 13

AccelStepper verStepper(AccelStepper::DRIVER, VER_STEP, VER_DIR);
AccelStepper horStepper(AccelStepper::DRIVER, HOR_STEP, HOR_DIR);

void initSteppers()
{
  pinMode(EN_PIN, OUTPUT);
  pinMode(SWITCH_VER, INPUT_PULLUP);
  pinMode(SWITCH_HOR, INPUT_PULLUP);

  verStepper.setMaxSpeed(200);
  verStepper.setAcceleration(100);
  horStepper.setMaxSpeed(200);
  horStepper.setAcceleration(100);
}

void enableSteppers()
{
  digitalWrite(EN_PIN, LOW); // Enable the stepper drivers
}

void disableSteppers()
{
  digitalWrite(EN_PIN, HIGH); // Disable the stepper drivers
}

void stepperMoveToPosition(AccelStepper &stepper, int position)
{
  stepper.setCurrentPosition(0);
  stepper.moveTo(position);

  while (stepper.distanceToGo() != 0)
  {
    stepper.run();
  }
}

void steppersMoveToPosition(int xPosition, int yPosition)
{
  verStepper.setCurrentPosition(0);
  horStepper.setCurrentPosition(0);

  verStepper.moveTo(xPosition);
  horStepper.moveTo(yPosition);

  while (verStepper.distanceToGo() != 0 || horStepper.distanceToGo() != 0)
  {
    verStepper.run();
    horStepper.run();
  }
}

#endif //_STEPPERCONTROL_H_