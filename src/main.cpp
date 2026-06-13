#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "LineFollow.h"
#include "Encoders.h"
#include "ColorSensors.h"
#include "Sonar.h"
#include "ServoControl.h"

#include "Arena/blue.h"
#include "Arena/red.h"

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    initEncoders();
    initSensors();
    initMotors();
    colorSensorsBegin();
    initServos();
    Serial.println("Code Running...");

    // rightTurnEncoder(200, 170);
    // forwardDistance(20.0f);
    // forward(50, 55);

    // linefollowFiveStrips(2);
    // delay(3000);
    // leftTurnEncoder(200, 180);
    // dropPellets();
    // blueStart();
    redStart();
    // if you have an arena button connected then use this
    // #define ARENA_BUTTON 13
    // #ifdef ARENA_BUTTON
    //     pinMode(ARENA_BUTTON, INPUT_PULLUP);

    //     if (digitalRead(ARENA_BUTTON) == LOW)
    //     {
    // blueStart();
    //     }
    //     else
    //     {
    //         redStart();
    //     }
    // #endif // ARENA_BUTTON
    // enableSteppers();
    // steppersMoveToPosition(500, 400);
    // delay(1000);
    // steppersMoveToPosition(-500, -400);
}

void loop()
{
    // loadAndShoot();
    // delay(1000);
    // for (int i = 60; i<=120; i++)
    // {
    //     shootServo.write(i);
    //     delay(15);
    // }
    // for (int i = 120; i>=60; i--)
    // {
    //     shootServo.write(i);
    //     delay(15);
    // }
    // leftInverse();
    // backward(50, 50);
    // Serial.println("Loop");
    // or for full debug output:
    // leftServo.write(10);
    // rightServo.write(125);
    // debugChannel(0);
    // debugChannel(1);
    // debugChannel(2);
    // debugChannel(3);
    debugChannel(4);
    Serial.println("============");

    // Serial.print(digitalRead(SWITCH_HOR));
    // Serial.print(" ");
    // Serial.println(digitalRead(SWITCH_VER));

    // printDipValues();

    // Results result = readSlotSensors();
    // Serial.print(result.left);
    // Serial.print(" ");
    // Serial.println(result.right);

    // printSensorVals(frontSensors);
    // printSensorVal(leftSensor);
    // printEncoders();
    // Serial.println(digitalRead(SWITCH_HOR));

    // Serial.println(getDistanceCM());

    // delay(300);
}