#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "StepperControl.h"
#include "LineFollow.h"
#include "Encoders.h"

#include "Arena/blue.h"
#include "Arena/red.h"

// Positive Value is up for vertical and right for horizonal

void setup()
{
    Serial.begin(9600);
    initEncoders();
    initSensors();
    initMotors();
    initSteppers();
    disableSteppers();

    Serial.println("Code Running...");

    // redStart();
    // if you have an arena button connected then use this
    // #define ARENA_BUTTON 13
    // #ifdef ARENA_BUTTON
    //     pinMode(ARENA_BUTTON, INPUT_PULLUP);

    //     if (digitalRead(ARENA_BUTTON) == LOW)
    //     {
    //         blueStart();
    //     }
    //     else
    //     {
    //         redStart();
    //     }
    // #endif // ARENA_BUTTON
    // linefollowFiveStrips(4, FORWARD, 100);
    // delay(2000);
    // leftTurnEncoder(200, 150);
    // delay(2000);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(3);
    // delay(2000);
    // leftTurnEncoder(200, 150);
    // delay(2000);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(4);
    // delay(2000);
    // rightTurnEncoder(210);
    // delay(2000);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(5);
    // delay(2000);
    // rightTurnEncoder(210);
    // delay(2000);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(2);
    // halt();
    forward(100, 100);
}

void loop()
{
    // linefollowWithFive(FORWARD);
    // steppersMoveToPosition(1000000, 1000000);
    // delay(5000);
    // Serial.println("Loop");
    // leftInverse();
    // leftTurnEncoder(200);
    // while (true)
    // {
    //     delay(10);
    // }

    // lineFollow(FORWARD, 50);
    // leftInverse();

    // printSensorVals(frontSensors);
    // printSensorVal(rightSensor);
    // delay(100);
    // printEncoders();
    // Serial.println(digitalRead(SWITCH_HOR));
}