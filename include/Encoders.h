#pragma once

#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include <Arduino.h>

typedef struct
{
    uint8_t pin;
    uint32_t ticks;
} Encoder;

Encoder _leftEncoder = {pin : 2, ticks : 0};
Encoder _rightEncoder = {pin : 3, ticks : 0};

void _leftInterruptRoutine()
{
    ++_leftEncoder.ticks;
}

void _rightInterruptRoutine()
{
    ++_rightEncoder.ticks;
}

void initEncoders()
{
    attachInterrupt(digitalPinToInterrupt(_leftEncoder.pin), _leftInterruptRoutine, RISING);
    attachInterrupt(digitalPinToInterrupt(_rightEncoder.pin), _rightInterruptRoutine, RISING);
}

void printEncoders()
{
    Serial.print(_leftEncoder.ticks);
    Serial.print(" ");
    Serial.print(_rightEncoder.ticks);
    Serial.println();
}

#endif //_ENCODERS_H_