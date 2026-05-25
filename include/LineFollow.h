#pragma once

#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"

int targetValFront = 570;
int targetValLeft = 300;
int baseSpeed = 150;

long integral = 0; // Accumulated error

void lineFollow(char direction = 'f', int speed = 150)
{
    // black -> 1, white -> 0
    bool l, m, r;

    if (direction == 'f')
    {
        l = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(frontSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(frontSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            forward(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            leftInverse(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            rightInverse(speed, speed);
        }
        else
        {
            forward(speed, speed);
        }
    }
    else if (direction == 'b')
    {
        l = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(backSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(backSensors[2]) > BLACK_VALUE ? 0 : 1;

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
    else if (direction == 'l')
    {
        l = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(leftSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            left(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            left(speed, speed);
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
            left(speed, speed);
        }
    }
    else if (direction == 'r')
    {
        l = analogRead(rightSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(rightSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            // Serial.println("Left");
            leftInverse(speed, speed);
            // forward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            rightInverse(speed, speed);
            // backward(speed, speed);
        }
        else
        {
            // Serial.println("Back");
            right(speed, speed);
        }
    }
}

void lineFollowV3(char direction = 'f', int speed = 150)
{
    // black -> 1, white -> 0
    bool l, m, r;

    if (direction == 'f')
    {
        l = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(frontSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(frontSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            forward(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            leftInverse(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            rightInverse(speed, speed);
        }
        else
        {
            forward(speed, speed);
        }
    }
    else if (direction == 'b')
    {
        l = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(backSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(backSensors[2]) > BLACK_VALUE ? 0 : 1;

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
    else if (direction == 'l')
    {
        l = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(leftSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            left(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            left(speed, speed);
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
            left(speed, speed);
        }
    }
    else if (direction == 'r')
    {
        l = analogRead(rightSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(rightSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;

        int ll = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
        int lm = analogRead(leftSensors[1]) > BLACK_VALUE ? 0 : 1;
        int lr = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            // Serial.println("Left");
            leftInverse(speed, speed);
            // forward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            rightInverse(speed, speed);
            // backward(speed, speed);
        }
        else if (ll == 1 && lm == 0 && lr == 0)
        {
            backward(speed + 20, speed + 20);
        }
        else if (ll == 0 && lm == 0 && lr == 1)
        {
            forward(speed + 20, speed + 20);
        }
        else
        {
            // Serial.println("Back");
            right(speed, speed);
        }
    }
}

void lineFollowV2(char direction = 'f', int speed = 150)
{
    // black -> 1, white -> 0
    bool l, m, r;

    if (direction == 'f')
    {
        l = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(frontSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(frontSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            forward(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            left(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            right(speed, speed);
        }
        else
        {
            forward(speed, speed);
        }
    }
    else if (direction == 'b')
    {
        l = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(backSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(backSensors[2]) > BLACK_VALUE ? 0 : 1;

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
            left(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            right(speed, speed);
        }
        else
        {
            // Serial.println("Back");
            backward(speed, speed);
        }
    }
    else if (direction == 'l')
    {
        l = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(leftSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            left(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            left(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            // Serial.println("Left");
            backward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            forward(speed, speed);
        }
        else
        {
            // Serial.println("Back");
            left(speed, speed);
        }
    }
    else if (direction == 'r')
    {
        l = analogRead(rightSensors[0]) > BLACK_VALUE ? 0 : 1;
        m = analogRead(rightSensors[1]) > BLACK_VALUE ? 0 : 1;
        r = analogRead(rightSensors[2]) > BLACK_VALUE ? 0 : 1;

        if (l == 1 && m == 1 && r == 1)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            // Serial.println("Back");
            right(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            // Serial.println("Left");
            // leftInverse(speed, speed);
            forward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            // Serial.println("Right");
            // rightInverse(speed, speed);
            backward(speed, speed);
        }
        else
        {
            // Serial.println("Back");
            right(speed, speed);
        }
    }
}

void lineFollowStrips(int stripsToMove, char direction = 'f', int speed = 150)
{
    int stripCount = 0;
    while (true)
    {
        int sensorOnLine = 0;

        if (direction == 'f')
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensors[2]) > BLACK_VALUE ? 0 : 1;
        }
        else if (direction == 'b')
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(leftSensors[0]) > BLACK_VALUE ? 0 : 1;
        }
        else if (direction == 'l')
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(frontSensors[0]) > BLACK_VALUE ? 0 : 1;
        }
        else if (direction == 'r')
        {
            // Black -> 1, White -> 0
            sensorOnLine = analogRead(backSensors[0]) > BLACK_VALUE ? 0 : 1;
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

void lineFollowEncoder(uint32_t ticksToMove, char direction = 'f', int speed = 150)
{
    flEncoder.ticks = 0;
    while (flEncoder.ticks < ticksToMove)
    {
        Serial.println();
        lineFollow(direction, speed);
    }
    halt();
}

void linefollowFrontPid()
{
    float Kp = 0.09;
    float Ki = 0.001;

    // Sensor and error
    int sensorValue = analogRead(frontSensors[1]);
    int error = targetValFront - sensorValue;

    // Integrate error (avoid windup by limiting)
    integral += error;
    integral = constrain(integral, -1000, 1000); // anti-windup

    int correction = (Kp * error) + (Ki * integral);
    Serial.println(correction);

    int leftSpeed = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;

    // Limit PWM values between 0 and 255
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    forward(leftSpeed, rightSpeed);
}

void linefollowFrontPidWithEncoder(uint32_t ticksToMove)
{
    flEncoder.ticks = 0;
    float Kp = 0.09;
    float Ki = 0.001;
    while (flEncoder.ticks < ticksToMove)
    {

        // Sensor and error
        int sensorValue = analogRead(frontSensors[1]);
        int error = targetValFront - sensorValue;

        // Integrate error (avoid windup by limiting)
        integral += error;
        integral = constrain(integral, -1000, 1000); // anti-windup

        int correction = (Kp * error) + (Ki * integral);
        Serial.println(correction);

        int leftSpeed = baseSpeed - correction;
        int rightSpeed = baseSpeed + correction;

        // Limit PWM values between 0 and 255
        leftSpeed = constrain(leftSpeed, 0, 255);
        rightSpeed = constrain(rightSpeed, 0, 255);

        forward(leftSpeed, rightSpeed);
    }
}

#endif //_LINEFOLLOW_H