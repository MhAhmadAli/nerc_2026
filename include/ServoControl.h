#pragma once

#ifndef _SERVOCONTROL_H_
#define _SERVOCONTROL_H_

#include <Arduino.h>
#include <Servo.h>

#define VER_SERVO_PIN 12
#define HOR_SERVO_PIN 13

#define FLAP_SERVO_PIN 11
#define SHOOT_SERVO_PIN 10

#define LEFT_SERVO 9
#define RIGHT_SERVO 8

// shoot 0 pos is loaded
// shoot 50 is to load

// flap 90 is open
// flap 0 is engaged

// left 140 is retracted
// left 0 is extended

// right 125 is extended
// right 0 is retracted

Servo verServo;
Servo horServo;

Servo flapServo;
Servo shootServo;

Servo leftServo;
Servo rightServo;

void initServos()
{
  verServo.attach(VER_SERVO_PIN);
  horServo.attach(HOR_SERVO_PIN);
  flapServo.attach(FLAP_SERVO_PIN);
  shootServo.attach(SHOOT_SERVO_PIN);

  leftServo.attach(LEFT_SERVO);
  rightServo.attach(RIGHT_SERVO);

  verServo.write(90);
  horServo.write(90);
  flapServo.write(90);
  shootServo.write(55);

  leftServo.write(130);
  rightServo.write(0);
}

void loadAndShoot()
{
  flapServo.write(90);
  shootServo.write(55);
  delay(300);
  flapServo.write(0);
  delay(300);
  shootServo.write(0);
  delay(300);
  flapServo.write(90);
}


#endif //_SERVOCONTROL_H_