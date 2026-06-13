#pragma once

#ifndef _COLORSENSORS_H_
#define _COLORSENSORS_H_

#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "ServoControl.h"
#include "LineFollow.h"

#define PCA_ADDR 0x70
#define LED_PIN 22
#define SENSOR_COUNT 5

Adafruit_TCS34725 *tcs = nullptr;

static const int CHANNELS[] = {2, 3, 6, 7, 5};

#define TOP_LEFT_CHANNEL 0
#define BOTTOM_LEFT_CHANNEL 1
#define BOTTOM_RIGHT_CHANNEL 2

#define LEFT_SERVO_CHANNEL 3
static const uint8_t RIGHT_SERVO_CHANNEL = 4;
struct Results
{
  bool top_left;
  bool top_right;
  bool bottom_left;
  bool bottom_right;
};
struct ColorData
{
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t c;
};

void debugChannel(uint8_t);

void tcaSelect(uint8_t channel)
{
  Wire.beginTransmission(PCA_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

ColorData readAveraged(uint8_t channel)
{
  ColorData d = {0, 0, 0, 0};

  tcaSelect(channel);
  delay(160);

  for (int i = 0; i < 5; i++)
  {
    uint16_t r, g, b, c;
    tcs->getRawData(&r, &g, &b, &c);
    d.r += r;
    d.g += g;
    d.b += b;
    d.c += c;
    delay(5);
  }

  d.r /= 5;
  d.g /= 5;
  d.b /= 5;
  d.c /= 5;

  return d;
}

String detectColor(ColorData d)
{
  if (d.c < 60)
    return "NO_OBJECT";

  float rf = (float)d.r / d.c;
  float gf = (float)d.g / d.c;
  float bf = (float)d.b / d.c;

  if (bf > 0.38 && bf > rf + 0.10 && bf > gf + 0.10)
    return "BLUE";

  if (rf > 0.32 && rf > bf + 0.12 && rf > gf + 0.12)
    return "RED";

  return "UNKNOWN";
}

String readColor(uint8_t channel)
{
  return detectColor(readAveraged(CHANNELS[channel]));
}

Results readSlotSensors()
{
  String color1 = readColor(TOP_LEFT_CHANNEL);
  String color3 = readColor(BOTTOM_LEFT_CHANNEL);
  String color4 = readColor(BOTTOM_RIGHT_CHANNEL);

  Results res;
  res.top_left = !(color1 == "RED");
  res.bottom_left = !(color3 == "RED");
  res.bottom_right = !(color4 == "RED");

  uint8_t detectedCount = res.top_left + res.bottom_left + res.bottom_right;

  // Exactly 2 of the 4 slots should have a pellet at any time.
  if (detectedCount == 1)
  {
    res.top_right = true;
  }
  else if (detectedCount == 2)
  {
    res.top_right = false;
  }
  else
  {
    Serial.print("WARNING: readSlotSensors saw ");
    Serial.print(detectedCount);
    Serial.println(" of 3 sensors active (expected 1 or 2)");
    res.top_right = false;
  }

  return res;
}

char detectBoxDirection(int servo1Angle = 15, int servo2Angle = 130)
{
  leftServo.write(servo1Angle);
  rightServo.write(servo2Angle);
  for (int i = 0; i < 3; i++)
  {
    debugChannel(4);
  }
  // Check right side first
  if (readColor(RIGHT_SERVO_CHANNEL) == "BLUE")
  {
    leftServo.write(130);
    rightServo.write(0);
    return 'r';
  }

  // Then left side
  if (readColor(LEFT_SERVO_CHANNEL) == "BLUE")
  {
    leftServo.write(130);
    rightServo.write(0);
    return 'l';
  }

  // Then front (any of the 4 slot sensors)
  // Results front = readSlotSensors();
  // if (front.bottom_left || front.bottom_right)
  // {
  //   leftServo.write(130);
  //   rightServo.write(0);
  //   return 'f';
  // }

  leftServo.write(130);
  rightServo.write(0);
  // // Nothing detected on right, left, or front
  return 'b';
}

void debugChannel(uint8_t channel)
{
  ColorData d = readAveraged(CHANNELS[channel]);

  Serial.print("CH");
  Serial.print(channel);
  Serial.print(" R=");
  Serial.print(d.r);
  Serial.print(" G=");
  Serial.print(d.g);
  Serial.print(" B=");
  Serial.print(d.b);
  Serial.print(" C=");
  Serial.print(d.c);
  Serial.print(" | rf=");
  Serial.print((float)d.r / d.c, 3);
  Serial.print(" gf=");
  Serial.print((float)d.g / d.c, 3);
  Serial.print(" bf=");
  Serial.print((float)d.b / d.c, 3);
  Serial.print(" => ");
  Serial.println(detectColor(d));
}

void colorSensorsBegin()
{
  tcs = new Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_60X);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  for (uint8_t i = 0; i < SENSOR_COUNT; i++)
  {
    tcaSelect(CHANNELS[i]);
    delay(50);

    if (tcs->begin())
      Serial.print("Sensor OK CH");
    else
      Serial.print("Sensor FAIL CH");

    Serial.println(i);
  }
}

void dropPellets(bool isHome = true)
{
  Results result = readSlotSensors();
  Serial.print("Detect: TL=");
  Serial.print(result.top_left);
  Serial.print(" TR=");
  Serial.print(result.top_right);
  Serial.print(" BL=");
  Serial.print(result.bottom_left);
  Serial.print(" BR=");
  Serial.println(result.bottom_right);

  // Bottom left
  if (result.bottom_left)
  {
    horServo.write(110);
    verServo.write(110);
    delay(200);
    loadAndShoot();
    delay(300);
  }

  // Bottom right
  if (result.bottom_right)
  {
    horServo.write(70);
    verServo.write(110);
    delay(200);
    loadAndShoot();
    delay(300);
  }

  // Top left
  if (result.top_left)
  {
    horServo.write(110);
    verServo.write(70);
    delay(200);
    loadAndShoot();
    delay(300);
  }

  // Top right
  if (result.top_right)
  {
    horServo.write(70);
    verServo.write(70);
    delay(200);
    loadAndShoot();
    delay(300);
  }

  delay(500);
}

#endif // _COLORSENSORS_H_