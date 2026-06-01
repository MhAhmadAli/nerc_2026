#pragma once

#ifndef _MOTORS_H_
#define _MOTORS_H_

#include <Arduino.h>
#include "Sensors.h"
#include "Encoders.h"

typedef struct
{
    uint8_t fwd_pin;
    uint8_t rev_pin;
} Motor;

Motor LEFT = {fwd_pin : 4, rev_pin : 5};
Motor RIGHT = {fwd_pin : 6, rev_pin : 7};

bool prevLine = false;

unsigned long previousMillis = 0; // Store the last time sensor was checked
const unsigned long intervalMillis = 300;

void initMotors()
{
    pinMode(LEFT.fwd_pin, OUTPUT);
    pinMode(LEFT.rev_pin, OUTPUT);
    pinMode(RIGHT.fwd_pin, OUTPUT);
    pinMode(RIGHT.rev_pin, OUTPUT);
}

void moveOneMotor(const Motor &motor, int speed)
{
    analogWrite(motor.fwd_pin, speed);
    analogWrite(motor.rev_pin, 0);
}

void halt()
{
    noInterrupts();
    analogWrite(LEFT.fwd_pin, 0);
    analogWrite(LEFT.rev_pin, 0);

    analogWrite(RIGHT.fwd_pin, 0);
    analogWrite(RIGHT.rev_pin, 0);

    interrupts();
}

void forward(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, leftSpeed);
    analogWrite(LEFT.rev_pin, 0);

    analogWrite(RIGHT.fwd_pin, rightSpeed);
    analogWrite(RIGHT.rev_pin, 0);
}

void forwardStrips(int stripsToMove, int speed = 50)
{
    int stripCount = 0;
    while (true)
    {
        int sensorOnLine = 0;

        // Black -> 1, White -> 0
        sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;

        unsigned long currentMillis = millis();
        if (sensorOnLine && !prevLine)
        {
            stripCount++;
            prevLine = true;
            previousMillis = currentMillis;
        }
        else if (currentMillis - previousMillis > intervalMillis)
        {
            prevLine = false;
        }

        if (stripCount < stripsToMove)
        {
            forward(speed, speed);
        }
        else
        {
            halt();
            return;
        }
    }
}

void backward(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, 0);
    analogWrite(LEFT.rev_pin, leftSpeed);

    analogWrite(RIGHT.fwd_pin, 0);
    analogWrite(RIGHT.rev_pin, rightSpeed);
}

void backwardStrips(int stripsToMove, int speed = 50)
{
    int stripCount = 0;
    while (true)
    {
        int sensorOnLine = 0;

        // Black -> 1, White -> 0
        sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;

        unsigned long currentMillis = millis();
        if (sensorOnLine && !prevLine)
        {
            stripCount++;
            prevLine = true;
            previousMillis = currentMillis;
        }
        else if (currentMillis - previousMillis > intervalMillis)
        {
            prevLine = false;
        }

        if (stripCount < stripsToMove)
        {
            backward(speed, speed);
        }
        else
        {
            halt();
            return;
        }
    }
}

void _right(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, leftSpeed);
    analogWrite(LEFT.rev_pin, 0);

    analogWrite(RIGHT.fwd_pin, 0);
    analogWrite(RIGHT.rev_pin, rightSpeed);
}

void rightInverse(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, leftSpeed);
    analogWrite(LEFT.rev_pin, 0);

    analogWrite(RIGHT.fwd_pin, 0);
    analogWrite(RIGHT.rev_pin, rightSpeed);
}

void _rightFreeze(int leftSpeed = 0, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, leftSpeed);
    analogWrite(LEFT.rev_pin, 0);

    analogWrite(RIGHT.fwd_pin, 0);
    analogWrite(RIGHT.rev_pin, rightSpeed);
}

void _left(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, 0);
    analogWrite(LEFT.rev_pin, leftSpeed);

    analogWrite(RIGHT.fwd_pin, rightSpeed);
    analogWrite(RIGHT.rev_pin, 0);
}

void leftInverse(int leftSpeed = 50, int rightSpeed = 50)
{
    analogWrite(LEFT.fwd_pin, 0);
    analogWrite(LEFT.rev_pin, leftSpeed);

    analogWrite(RIGHT.fwd_pin, rightSpeed);
    analogWrite(RIGHT.rev_pin, 0);
}

void _leftFreeze(int leftSpeed = 50, int rightSpeed = 0)
{
    analogWrite(LEFT.fwd_pin, 0);
    analogWrite(LEFT.rev_pin, leftSpeed);

    analogWrite(RIGHT.fwd_pin, rightSpeed);
    analogWrite(RIGHT.rev_pin, 0);
}

void leftTurnEncoder(uint32_t ticksToMove, int speed = 50)
{
    _leftEncoder.ticks = 0;
    while (_leftEncoder.ticks < ticksToMove)
    {
        leftInverse(speed, speed);
        interrupts();
    }
    halt();
}

void rightTurnEncoder(uint32_t ticksToMove)
{
    _leftEncoder.ticks = 0;
    while (_leftEncoder.ticks < ticksToMove)
    {
        rightInverse();
        interrupts();
    }
    halt();
}

void encoderMove(uint32_t ticksToMove)
{
    _leftEncoder.ticks = 0;
    while (_leftEncoder.ticks < ticksToMove)
    {
        Serial.print("");
        // printEncoders();
        // delay(1);
    }
    halt();
}

#endif //_MOTORS_H