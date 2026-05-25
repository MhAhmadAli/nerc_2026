#pragma once

#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include <Arduino.h>

typedef struct
{
    uint8_t pin;
    uint32_t ticks;
} Encoder;

Encoder flEncoder = {pin : 3, ticks : 0};
Encoder frEncoder = {pin : 2, ticks : 0};
Encoder rlEncoder = {pin : 18, ticks : 0};
Encoder rrEncoder = {pin : 19, ticks : 0};

void flInterruptRoutine()
{
    ++flEncoder.ticks;
}

void frInterruptRoutine()
{
    ++frEncoder.ticks;
}

void rlInterruptRoutine()
{
    ++rlEncoder.ticks;
}

void rrInterruptRoutine()
{
    ++rrEncoder.ticks;
}

void initEncoders()
{
    attachInterrupt(digitalPinToInterrupt(flEncoder.pin), flInterruptRoutine, RISING);
    attachInterrupt(digitalPinToInterrupt(frEncoder.pin), frInterruptRoutine, RISING);
    attachInterrupt(digitalPinToInterrupt(rlEncoder.pin), rlInterruptRoutine, RISING);
    attachInterrupt(digitalPinToInterrupt(rrEncoder.pin), rrInterruptRoutine, RISING);
}

void printEncoders()
{
    Serial.print(flEncoder.ticks);
    Serial.print(" ");
    Serial.print(frEncoder.ticks);
    Serial.print(" ");
    Serial.print(rlEncoder.ticks);
    Serial.print(" ");
    Serial.println(rrEncoder.ticks);
}

#endif //_ENCODERS_H_