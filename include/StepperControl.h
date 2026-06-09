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

#define HOLDER_IN1 13
#define HOLDER_IN2 12
#define HOLDER_IN3 3
#define HOLDER_IN4 2

#define SWITCH_VER 30
#define SWITCH_HOR 28

const int VER_POSITIONS[] = {0, 500};
const int HOR_POSITIONS[] = {0, 350};

int currentVerPosition = 0;
int currentHorPosition = 0;

// Grid positions: {row, col}  (row 0 = bottom, row 1 = top)
//                             (col 0 = left,   col 1 = right)
struct GridPos { int row; int col; };

const GridPos BOTTOM_LEFT  = {0, 0};
const GridPos BOTTOM_RIGHT = {0, 1};
const GridPos TOP_LEFT     = {1, 0};
const GridPos TOP_RIGHT    = {1, 1};

AccelStepper verStepper(AccelStepper::DRIVER, VER_STEP, VER_DIR);
AccelStepper horStepper(AccelStepper::DRIVER, HOR_STEP, HOR_DIR);

AccelStepper holderStepper(AccelStepper::HALF4WIRE, HOLDER_IN1, HOLDER_IN3, HOLDER_IN2, HOLDER_IN4);

void initSteppers()
{
  pinMode(EN_PIN, OUTPUT);
  pinMode(SWITCH_VER, INPUT_PULLUP);
  pinMode(SWITCH_HOR, INPUT_PULLUP);

  verStepper.setMaxSpeed(200);
  verStepper.setAcceleration(100);
  horStepper.setMaxSpeed(200);
  horStepper.setAcceleration(100);

  holderStepper.setMaxSpeed(1000);
  holderStepper.setAcceleration(500);
}

void enableSteppers()
{
  digitalWrite(EN_PIN, LOW); // Enable the stepper drivers
}

void disableSteppers()
{
  digitalWrite(EN_PIN, HIGH); // Disable the stepper drivers
}

void holderNextPosition()
{
  holderStepper.setCurrentPosition(0);

  // 1 full revolution is 4096 in half step mode
  // we need to move 1/8th to drop the pellet.
  holderStepper.moveTo(512);

  while (holderStepper.distanceToGo() != 0)
    holderStepper.run();
}

void steppersResetToHome()
{
  verStepper.setCurrentPosition(0);
  horStepper.setCurrentPosition(0);

  // Back off any switch already pressed at startup
  if (!digitalRead(SWITCH_VER))
  {
    verStepper.moveTo(50);
    while (verStepper.distanceToGo() != 0)
      verStepper.run();
  }

  if (!digitalRead(SWITCH_HOR))
  {
    horStepper.moveTo(50);
    while (horStepper.distanceToGo() != 0)
      horStepper.run();
  }

  // Now home normally
  verStepper.setCurrentPosition(0);
  horStepper.setCurrentPosition(0);

  verStepper.moveTo(-999);
  horStepper.moveTo(-999);

  bool verHomed = false;
  bool horHomed = false;

  while (!verHomed || !horHomed)
  {
    if (!verHomed)
    {
      if (digitalRead(SWITCH_VER))
        verStepper.run();
      else
        verHomed = true;
    }

    if (!horHomed)
    {
      if (digitalRead(SWITCH_HOR))
        horStepper.run();
      else
        horHomed = true;
    }
  }
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

void steppersMoveToPosition(int verPosition, int horPosition)
{
  verStepper.setCurrentPosition(0);
  horStepper.setCurrentPosition(0);

  verStepper.moveTo(verPosition);
  horStepper.moveTo(horPosition);

  while (verStepper.distanceToGo() != 0 || horStepper.distanceToGo() != 0)
  {
    verStepper.run();
    horStepper.run();
  }
}

void moveToGridPosition(GridPos position)
{
  int verTarget = VER_POSITIONS[position.row];
  int horTarget = HOR_POSITIONS[position.col];

  // Move relative to last known position
  verStepper.move(verTarget - currentVerPosition);
  horStepper.move(horTarget - currentHorPosition);

  while (verStepper.distanceToGo() != 0 || horStepper.distanceToGo() != 0)
  {
    verStepper.run();
    horStepper.run();
  }

  // Update tracked position
  currentVerPosition = verTarget;
  currentHorPosition = horTarget;
}

#endif //_STEPPERCONTROL_H_