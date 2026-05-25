#pragma once

#ifndef _SERVOCONTROL_H_
#define _SERVOCONTROL_H_

#include <Arduino.h>
#include <Wire.h>

#define I2C_SLAVE 4
#define I2C_DATA_SIZE 4

#define BASE_000 10  // LEFT AT FRONT
#define BASE_090 70  // CENTER AT FRONT
#define BASE_180 135 // RIGHT AT FRONT

#define FRONT_SERVO "FT"
#define LEFT_SERVO "LT"
#define RIGHT_SERVO "RT"
#define BASE_SERVO "BS"

enum RedServo
{
    SERVO_NONE,
    SERVO_CENT,
    SERVO_LEFT,
    SERVO_RGHT,
};

void initServos()
{
    Wire.begin();
}

void sendCommand(String cmd)
{
    Wire.beginTransmission(I2C_SLAVE);
    Wire.write(cmd.c_str());
    Wire.endTransmission();
}

RedServo getRedServo()
{
    Wire.requestFrom(I2C_SLAVE, I2C_DATA_SIZE); // request 6 bytes from slave device #8

    String data = "";
    while (Wire.available())
    {                         // slave may send less than requested
        char c = Wire.read(); // receive a byte as character
        data += c;
    }
    Serial.println(data);

    if (data.indexOf("LEFT") > -1)
    {
        return RedServo::SERVO_LEFT;
    }
    else if (data.indexOf("CENT") > -1)
    {
        return RedServo::SERVO_CENT;
    }
    else
    {
        return RedServo::SERVO_RGHT;
    }
}

void moveServo(String servo, int pos)
{
    sendCommand(servo + " " + String(pos));
}

#endif //_SERVOCONTROL_H_