#pragma once
// 0 0 1
// 1 0 0
// 0 0 1

#ifndef _RED15_H_
#define _RED15_H_

#include <Arduino.h>
#include "LineFollow.h"
#include "ServoControl.h"

void red15()
{
    sendCommand("FL LT OPEN");
    moveServo(LEFT_SERVO, 0);
    lineFollowStrips(4, 'f', 170);
    delay(200);
    rightTurnEncoder(780);
    delay(200);
    lineFollowEncoder(320, 'f', 80);
    delay(500);
    sendCommand("FL LT CLOSE");
    delay(300);
    moveServo(LEFT_SERVO, 70);
    delay(500);

    moveServo(BASE_SERVO, BASE_090);
    delay(800);
    sendCommand("FL FT OPEN");
    moveServo(FRONT_SERVO, 0);
    lineFollowStrips(3, 'f');
    delay(300);
    leftTurnEncoder(780);
    delay(500);
    lineFollowEncoder(330, 'f', 80);
    delay(500);
    sendCommand("FL FT CLOSE");
    delay(300);
    moveServo(FRONT_SERVO, 70);
    delay(500);

    moveServo(BASE_SERVO, BASE_000);
    delay(800);
    sendCommand("FL RT OPEN");
    moveServo(RIGHT_SERVO, 0);
    lineFollowStrips(1, 'b');
    delay(500);
    lineFollowEncoder(330, 'b', 80);
    delay(500);
    sendCommand("FL RT CLOSE");
    delay(300);
    moveServo(RIGHT_SERVO, 70);
    delay(500);

    lineFollowStrips(1, 'b');
    delay(300);

    RedServo redServo = getRedServo();
    if (redServo == RedServo::SERVO_LEFT)
    {
        moveServo(BASE_SERVO, BASE_000);
        delay(800);
        moveServo(LEFT_SERVO, 23);
        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(1, 'f');
        delay(300);
        rightTurnEncoder(780);
        delay(300);
        lineFollowEncoder(600, 'f');
        delay(100);
        sendCommand("FL LT OPEN");
        delay(300);

        lineFollowStrips(5, 'b', 170);
        lineFollowEncoder(400, 'b');
        moveServo(RIGHT_SERVO, 40);
        delay(500);
        sendCommand("FL RT OPEN");
        delay(300);
        lineFollowStrips(2, 'f');
        moveServo(LEFT_SERVO, 70);
        moveServo(RIGHT_SERVO, 70);
        delay(500);
        rightTurnEncoder(780);

        lineFollowEncoder(400, 'f');
        moveServo(BASE_SERVO, BASE_090);
        lineFollowStrips(4, 'f', 170);
        delay(300);
        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(1, 'f');
        delay(300);
        lineFollowEncoder(330, 'f', 80);
        delay(100);
        moveServo(FRONT_SERVO, 0);
        delay(800);
        sendCommand("FL FT OPEN");
        delay(300);
    }
    else if (redServo == RedServo::SERVO_CENT)
    {
        moveServo(BASE_SERVO, BASE_090);
        delay(800);
        moveServo(FRONT_SERVO, 23);
        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(1, 'f');
        delay(300);
        rightTurnEncoder(780);
        delay(300);
        lineFollowEncoder(600, 'f');
        delay(100);
        sendCommand("FL FT OPEN");
        delay(300);
        lineFollowStrips(5, 'b', 170);
        moveServo(FRONT_SERVO, 70);
        delay(500);

        moveServo(BASE_SERVO, BASE_000);
        delay(800);
        lineFollowEncoder(400, 'b');
        moveServo(RIGHT_SERVO, 40);
        delay(500);
        sendCommand("FL RT OPEN");
        delay(300);
        lineFollowStrips(2, 'f');
        moveServo(RIGHT_SERVO, 70);
        delay(500);

        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(4, 'f', 170);
        delay(300);
        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(1, 'f');
        delay(300);
        lineFollowEncoder(330, 'f', 80);
        delay(100);
        moveServo(LEFT_SERVO, 0);
        delay(500);
        sendCommand("FL LT OPEN");
        delay(300);
    }
    else if (redServo == RedServo::SERVO_RGHT)
    {
        leftTurnEncoder(780);
        lineFollowEncoder(400, 'b');
        moveServo(RIGHT_SERVO, 35);
        lineFollowStrips(1, 'b');
        delay(300);
        rightTurnEncoder(780);
        delay(300);
        lineFollowEncoder(600, 'b');
        delay(100);
        sendCommand("FL RT OPEN");
        delay(300);

        lineFollowStrips(5, 'f', 170);
        moveServo(RIGHT_SERVO, 70);
        delay(500);
        lineFollowEncoder(400, 'f');
        moveServo(LEFT_SERVO, 40);
        delay(500);
        sendCommand("FL LT OPEN");
        delay(300);
        lineFollowStrips(2, 'b');
        moveServo(LEFT_SERVO, 70);
        leftTurnEncoder(780);
        lineFollowEncoder(400, 'f');

        moveServo(BASE_SERVO, BASE_090);
        lineFollowStrips(4, 'f', 170);
        delay(300);
        rightTurnEncoder(780);
        lineFollowEncoder(400, 'f');
        lineFollowStrips(1, 'f');
        delay(300);
        lineFollowEncoder(330, 'f', 80);
        delay(100);
        moveServo(FRONT_SERVO, 0);
        delay(500);
        sendCommand("FL FT OPEN");
        delay(300);
    }

    lineFollowStrips(2, 'b');
    delay(300);
    leftTurnEncoder(780);
    lineFollowEncoder(1900, 'f', 255);
}

#endif //_RED15_H_