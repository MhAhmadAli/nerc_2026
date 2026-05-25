#pragma once

#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <Arduino.h>

#define NUM_SENSORS 3
#define BLACK_VALUE 600

// pins -> sensors left to right
const uint8_t frontSensors[NUM_SENSORS] = {A6, A12, A7};
const uint8_t backSensors[NUM_SENSORS] = {A0, A1, A2};
const uint8_t leftSensors[NUM_SENSORS] = {A3, A4, A5};
const uint8_t rightSensors[NUM_SENSORS] = {A14, A13, A15};

void setupSensorPins(const uint8_t pins[])
{
    for (size_t i = 0; i < NUM_SENSORS; i++)
    {
        pinMode(pins[i], INPUT);
    }
}

void initSensors()
{
    setupSensorPins(frontSensors);
    setupSensorPins(leftSensors);
    setupSensorPins(rightSensors);
    setupSensorPins(backSensors);
}

void printSensorVals(const uint8_t pins[], char end = '\n', char sep = ' ')
{
    for (size_t i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(analogRead(pins[i]));
        Serial.print(sep);
    }
    Serial.print(end);
}

#endif //_SENSORS_H