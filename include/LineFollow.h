#pragma once

#ifndef _LINEFOLLOW_H_
#define _LINEFOLLOW_H_

#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "Sonar.h"

enum Direction
{
    FORWARD = 'f',
    BACKWARD = 'b',
    LEFTWARD = 'l',
    RIGHTWARD = 'r'
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
            forward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            forward(speed, speed);
        }
        else if (l == 0 && m == 0 && r == 1)
        {
            leftInverse(speed, speed);
        }
        else if (l == 1 && m == 0 && r == 0)
        {
            rightInverse(speed, speed);
        }
        else
        {
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
            backward(speed, speed);
        }
        else if (l == 0 && m == 1 && r == 0)
        {
            backward(speed, speed);
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
            backward(speed, speed);
        }
    }
}

// Persistent state for ramping (motor speeds from the previous call)
static int currentL = 0;
static int currentR = 0;

const int RAMP_STEP = 15;     // how much speed can change per loop call (tune this)
const int TURN_GAIN = 1;     // how aggressively error maps to speed difference (tune this)

void lineFollowPropotional(Direction direction = FORWARD, int speed = 150)
{
    int lv, mv, rv;
    bool l, m, r;

    if (direction == FORWARD)
    {
        lv = analogRead(frontSensors[1]);
        mv = analogRead(frontSensors[2]);
        rv = analogRead(frontSensors[3]);
    }
    else // BACKWARD
    {
        lv = analogRead(backSensors[1]);
        mv = analogRead(backSensors[2]);
        rv = analogRead(backSensors[3]);
    }

    l = lv < BLACK_VALUE ? 0 : 1;
    m = mv < BLACK_VALUE ? 0 : 1;
    r = rv < BLACK_VALUE ? 0 : 1;

    int targetL, targetR;

    if (l == 0 && m == 0 && r == 0)
    {
        // Line completely lost — keep last known direction's correction
        // by holding previous speeds rather than snapping to a pivot.
        // (Optional: add a search routine here instead.)
        targetL = currentL;
        targetR = currentR;
    }
    else
    {
        // Weighted error: positive -> line is to the right, negative -> line is to the left
        // On the line (m=1) contributes 0; left sensor on line (l=1) -> error negative;
        // right sensor on line (r=1) -> error positive.
        int error = (r * 1) - (l * 1);

        // Scale error into a speed differential
        int correction = error * speed * TURN_GAIN;

        if (direction == FORWARD)
        {
            // Drifted right (error > 0) -> slow right wheel, speed up... actually
            // to steer back left, slow the right wheel relative to left.
            targetL = speed + correction; // when error<0 (drift left), left slows
            targetR = speed - correction; // when error>0 (drift right), right slows
        }
        else
        {
            // Reversed mapping for backward driving
            targetL = speed - correction;
            targetR = speed + correction;
        }

        targetL = constrain(targetL, 0, speed);
        targetR = constrain(targetR, 0, speed);
    }

    // Ramp current speeds toward target speeds to avoid sudden jerks
    if (currentL < targetL) currentL = min(currentL + RAMP_STEP, targetL);
    else if (currentL > targetL) currentL = max(currentL - RAMP_STEP, targetL);

    if (currentR < targetR) currentR = min(currentR + RAMP_STEP, targetR);
    else if (currentR > targetR) currentR = max(currentR - RAMP_STEP, targetR);

    if (direction == FORWARD)
        forward(currentL, currentR);
    else
        backward(currentL, currentR);
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
        }
        else
        {
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
        interrupts();
        lineFollow(direction, speed);
    }
    halt();
}

void lineFollowDistance(float distanceToStop, Direction direction = FORWARD, int speed = 50)
{
    float currentDistance = getDistanceCM();
    while (currentDistance > distanceToStop)
    {
        currentDistance = getDistanceCM();
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

// Persistent state for ramping (motor speeds from the previous call)
static int currentL5 = 0;
static int currentR5 = 0;

const int RAMP_STEP_5  = 8;   // max change in speed per call (tune this)
const float TURN_GAIN_5 = 1.0; // how aggressively error maps to speed difference (tune this)

void linefollowWithFivePropotional(Direction direction = FORWARD, int speed = 50)
{
    // black -> 1, white -> 0
    bool lm, l, m, r, rm;

    if (direction == FORWARD)
    {
        lm = analogRead(frontSensors[0]) < BLACK_VALUE ? 0 : 1;
        l  = analogRead(frontSensors[1]) < BLACK_VALUE ? 0 : 1;
        m  = analogRead(frontSensors[2]) < BLACK_VALUE ? 0 : 1;
        r  = analogRead(frontSensors[3]) < BLACK_VALUE ? 0 : 1;
        rm = analogRead(frontSensors[4]) < BLACK_VALUE ? 0 : 1;
    }
    else // BACKWARD
    {
        lm = analogRead(backSensors[0]) < BLACK_VALUE ? 0 : 1;
        l  = analogRead(backSensors[1]) < BLACK_VALUE ? 0 : 1;
        m  = analogRead(backSensors[2]) < BLACK_VALUE ? 0 : 1;
        r  = analogRead(backSensors[3]) < BLACK_VALUE ? 0 : 1;
        rm = analogRead(backSensors[4]) < BLACK_VALUE ? 0 : 1;
    }

    int targetL, targetR;

    // --- Hard recovery cases: line is almost off the edge of the array ---
    // Only pivot when the outermost sensor is on the line AND the center
    // has lost it — i.e. we're about to drive off the line entirely.
    bool hardLeft  = (lm == 1 && m == 0);
    bool hardRight = (rm == 1 && m == 0);

    if (hardLeft && !hardRight)
    {
        if (direction == FORWARD)
            leftInverse(speed, speed);
        else
            backward(speed, speed); // or your equivalent reverse-pivot
        currentL5 = currentR5 = speed; // reset ramp state so we don't jolt on exit
        return;
    }
    else if (hardRight && !hardLeft)
    {
        if (direction == FORWARD)
            rightInverse(speed, speed);
        else
            backward(speed, speed);
        currentL5 = currentR5 = speed;
        return;
    }

    // --- Normal case: proportional steering ---
    // Assign position weights to each sensor, left = negative, right = positive
    const int weights[5] = { -2, -1, 0, 1, 2 };
    bool sensors[5] = { lm, l, m, r, rm };

    int errorSum = 0;
    int activeCount = 0;

    for (int i = 0; i < 5; i++)
    {
        if (sensors[i])
        {
            errorSum += weights[i];
            activeCount++;
        }
    }

    if (activeCount == 0)
    {
        // Line completely lost between hard-turn checks above —
        // hold previous speeds rather than snapping.
        targetL = currentL5;
        targetR = currentR5;
    }
    else
    {
        // Average error across active sensors, normalized to [-1, 1]
        // (max |weight| = 2)
        float error = (float)errorSum / activeCount / 2.0;

        int correction = (int)(error * speed * TURN_GAIN_5);

        if (direction == FORWARD)
        {
            // error > 0 -> line is to the right -> slow right wheel to turn right
            targetL = speed + correction;
            targetR = speed - correction;
        }
        else
        {
            // reversed mapping for backward driving
            targetL = speed - correction;
            targetR = speed + correction;
        }

        targetL = constrain(targetL, 0, speed);
        targetR = constrain(targetR, 0, speed);
    }

    // Ramp toward target speeds to smooth out transitions
    if (currentL5 < targetL) currentL5 = min(currentL5 + RAMP_STEP_5, targetL);
    else if (currentL5 > targetL) currentL5 = max(currentL5 - RAMP_STEP_5, targetL);

    if (currentR5 < targetR) currentR5 = min(currentR5 + RAMP_STEP_5, targetR);
    else if (currentR5 > targetR) currentR5 = max(currentR5 - RAMP_STEP_5, targetR);

    if (direction == FORWARD)
        forward(currentL5, currentR5);
    else
        backward(currentL5, currentR5);
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
        }
        else
        {
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
        interrupts();
        linefollowWithFive(direction, speed);
    }
    halt();
}

void lineFollowFiveDistance(float distanceToStop, Direction direction = FORWARD, int speed = 50)
{
    float currentDistance = getDistanceCM();
    Serial.println(currentDistance > distanceToStop);
    while (currentDistance > distanceToStop)
    {
        Serial.println(currentDistance);
        currentDistance = getDistanceCM();
        linefollowWithFive(direction, speed);
    }
    halt();
}

#endif //_LINEFOLLOW_H