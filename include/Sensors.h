#pragma once

#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <Arduino.h>

#define NUM_SENSORS 5
#define BLACK_VALUE 750

// pins -> sensors left to right
const uint8_t frontSensors[NUM_SENSORS] = {A6, A9, A7, A8, A10};
const uint8_t backSensors[NUM_SENSORS] = {A15, A11, A12, A13, A14};
const uint8_t leftSensor = A5;
const uint8_t rightSensor = A4;

void setupSensorPin(const uint8_t pin)
{
    pinMode(pin, INPUT);
}

void setupSensorPins(const uint8_t pins[])
{
    for (size_t i = 0; i < NUM_SENSORS; i++)
    {
        setupSensorPin(pins[i]);
    }
}

void initSensors()
{
    setupSensorPins(frontSensors);
    setupSensorPins(backSensors);
    setupSensorPin(leftSensor);
    setupSensorPin(rightSensor);
}

void printSensorVal(const uint8_t pin, char end = '\n', char sep = ' ')
{
    Serial.print(analogRead(pin));
    Serial.print(sep);
    Serial.print(end);
}

void printSensorVals(const uint8_t pins[], char end = '\n', char sep = '\t')
{
    for (size_t i = 0; i < NUM_SENSORS; i++)
    {
        Serial.print(analogRead(pins[i]));
        Serial.print(sep);
    }
    Serial.print(end);
}

#endif //_SENSORS_H