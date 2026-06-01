#pragma once

#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"

enum Direction
{
    FORWARD = 'f',
    BACKWARD = 'b'
};

void lineFollow(Direction direction = FORWARD, int speed = 50)
{
    // black -> 1, white -> 0
    bool l, m, r;

    if (direction == FORWARD)
    {
        l = analogRead(frontSensors[1]) < BLACK_VALUE ? 0 : 1;
        m = analogRead(frontSensors[2]) < BLACK_VALUE ? 0 : 1;
        r = analogRead(frontSensors[3]) < BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            Serial.println("Forward");
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            Serial.println("Forward");
            forward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            Serial.println("Left");
            leftInverse(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            Serial.println("Right");
            rightInverse(speed, speed);
        }
        else
        {
            Serial.println("Forward");
            forward(speed, speed);
        }
    }
    else if (direction == BACKWARD)
    {
        l = analogRead(backSensors[1]) < BLACK_VALUE ? 0 : 1;
        m = analogRead(backSensors[2]) < BLACK_VALUE ? 0 : 1;
        r = analogRead(backSensors[3]) < BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            backward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            backward(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            // Serial.println("Left");
            leftInverse(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            rightInverse(speed, speed);
        }
        else
        {
            // Serial.println("Back");
            backward(speed, speed);
        }
    }
}

void lineFollowStrips(int stripsToMove, Direction direction = FORWARD, int speed = 50)
{
    int stripCount = 0;
    while (true)
    {
        int sensorOnLine = 0;

        if (direction == FORWARD)
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;
        }
        else if (direction == BACKWARD)
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;
        }

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
            lineFollow(direction, speed);
            // Serial.print("Strip# ");
            // Serial.println(stripCount);
        }
        else
        {
            // Serial.println("Halt!");
            halt();
            return;
        }
    }
}

void lineFollowEncoder(uint32_t ticksToMove, Direction direction = FORWARD, int speed = 50)
{
    _leftEncoder.ticks = 0;
    while (_leftEncoder.ticks < ticksToMove)
    {
        Serial.println();
        lineFollow(direction, speed);
    }
    halt();
}

void linefollowWithFive(Direction direction = FORWARD, int speed = 50)
{
    // black -> 1, white -> 0
    bool lm, l, m, r, rm;

    if (direction == FORWARD)
    {

        lm = analogRead(frontSensors[0]) < BLACK_VALUE ? 0 : 1;
        l = analogRead(frontSensors[1]) < BLACK_VALUE ? 0 : 1;
        m = analogRead(frontSensors[2]) < BLACK_VALUE ? 0 : 1;
        r = analogRead(frontSensors[3]) < BLACK_VALUE ? 0 : 1;
        rm = analogRead(frontSensors[4]) < BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 1)
        {
            leftInverse(speed, speed);
        }
        else if (lm == 0 && m == 1 && r == 1)
        {
            leftInverse(speed, speed);
        }
        else if (l == 1 && m == 1 && r == 0)
        {
            rightInverse(speed, speed);
        }
        else if (l == 1 && m == 1 && rm == 0)
        {
            rightInverse(speed, speed);
        }
        else
        {
            forward(speed);
        }
    }
    else if (direction == BACKWARD)
    {

        lm = analogRead(backSensors[0]) < BLACK_VALUE ? 0 : 1;
        l = analogRead(backSensors[1]) < BLACK_VALUE ? 0 : 1;
        m = analogRead(backSensors[2]) < BLACK_VALUE ? 0 : 1;
        r = analogRead(backSensors[3]) < BLACK_VALUE ? 0 : 1;
        rm = analogRead(backSensors[4]) < BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            backward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            backward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 1)
        {
            leftInverse(speed, speed);
        }
        else if (lm == 0 && m == 1 && r == 1)
        {
            leftInverse(speed, speed);
        }
        else if (l == 1 && m == 1 && r == 0)
        {
            rightInverse(speed, speed);
        }
        else if (l == 1 && m == 1 && rm == 0)
        {
            rightInverse(speed, speed);
        }
        else
        {
            backward(speed);
        }
    }
}

void linefollowFiveStrips(int stripsToMove, Direction direction = FORWARD, int speed = 50)
{
    int stripCount = 0;
    while (true)
    {
        int sensorOnLine = 0;

        if (direction == FORWARD)
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;
        }
        else if (direction == BACKWARD)
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensor) > BLACK_VALUE ? 0 : 1;
        }

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
            linefollowWithFive(direction, speed);
            // Serial.print("Strip# ");
            // Serial.println(stripCount);
        }
        else
        {
            // Serial.println("Halt!");
            halt();
            return;
        }
    }
}

void linefollowFiveEncoder(uint32_t ticksToMove, Direction direction = FORWARD, int speed = 50)
{
    _leftEncoder.ticks = 0;
    while (_leftEncoder.ticks < ticksToMove)
    {
        Serial.println();
        lineFollow(direction, speed);
    }
    halt();
}

#endif //_LINEFOLLOW_H