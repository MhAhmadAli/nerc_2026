#pragma once

#ifndef _COLORSENSORS_H_
#define _COLORSENSORS_H_

#include <Wire.h>
#include <Adafruit_TCS34725.h>

#define PCA_ADDR        0x70
#define LED_PIN         22
#define SENSOR_COUNT    3

Adafruit_TCS34725* tcs = nullptr;

struct ColorData
{
  uint16_t r;
  uint16_t g;
  uint16_t b;
  uint16_t c;
};

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
  delay(20);

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
  if (d.c < 60) return "NO_OBJECT";

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
  return detectColor(readAveraged(channel));
}

void debugChannel(uint8_t channel)
{
  ColorData d = readAveraged(channel);

  Serial.print("CH");   Serial.print(channel);
  Serial.print(" R=");  Serial.print(d.r);
  Serial.print(" G=");  Serial.print(d.g);
  Serial.print(" B=");  Serial.print(d.b);
  Serial.print(" C=");  Serial.print(d.c);
  Serial.print(" | rf="); Serial.print((float)d.r / d.c, 3);
  Serial.print(" gf=");   Serial.print((float)d.g / d.c, 3);
  Serial.print(" bf=");   Serial.print((float)d.b / d.c, 3);
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
    tcaSelect(i);
    delay(50);

    if (tcs->begin())
      Serial.print("Sensor OK CH");
    else
      Serial.print("Sensor FAIL CH");

    Serial.println(i);
  }
}

#endif // _COLORSENSORS_H_