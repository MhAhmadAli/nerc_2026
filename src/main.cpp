#include <Arduino.h>
#include "Sensors.h"
#include "Motors.h"
#include "StepperControl.h"
#include "LineFollow.h"
#include "Encoders.h"
#include "ColorSensors.h"

#include "Arena/blue.h"
#include "Arena/red.h"

// Positive Value is up for vertical and right for horizonal

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    initEncoders();
    initSensors();
    initMotors();
    initSteppers();
    colorSensorsBegin();
    delay(5000);
    enableSteppers();
    steppersResetToHome();
    delay(100);
    disableSteppers();
    // delay(5000);

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

    // linefollowFiveStrips(7, FORWARD, 50);
    // delay(500);
    // rightTurnEncoder(210, 150);
    // delay(1000);
    // linefollowFiveStrips(2, BACKWARD, 50);
    // delay(200);
    // linefollowFiveStrips(2, FORWARD, 50);
    // delay(1000);
    // linefollowFiveEncoder(150);
    // delay(200);
    // enableSteppers();
    // holderNextPosition();
    // steppersMoveToPosition(500, 350); // top right
    // holderNextPosition();
    // steppersResetToHome();
    // disableSteppers();
    // linefollowFiveEncoder(150, BACKWARD);
    // delay(500);
    // rightTurnEncoder(210, 150);
    // delay(500);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(4, FORWARD, 50);
    // delay(1000);
    // rightTurnEncoder(210, 150);
    // delay(1000);
    // linefollowFiveStrips(1, BACKWARD, 50);
    // delay(1000);
    // linefollowFiveStrips(2, FORWARD, 50);
    // enableSteppers();
    // steppersMoveToPosition(500, 0); // top left
    // holderNextPosition();
    // steppersMoveToPosition(0, 350); // bottom right
    // holderNextPosition();
    // disableSteppers();
    // delay(500);
    // linefollowFiveStrips(2, BACKWARD, 50);
    // delay(500);
    // linefollowFiveEncoder(70, FORWARD, 50);
    // delay(1000);
    // rightTurnEncoder(210, 150);
    // delay(1000);
    // linefollowFiveEncoder(200);
    // linefollowFiveStrips(2, FORWARD, 50);
    // delay(1000);
    // leftTurnEncoder(200, 150);
    // delay(1000);
    // lineFollowEncoder(200);
    // linefollowFiveStrips(5, FORWARD, 100);
    // forwardEncoder(1500, 70);

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
    // forward(100, 100);
    // steppersMoveToPosition(200, 200);
    delay(1000);
    enableSteppers();
    moveToGridPosition(TOP_RIGHT);
    // moveToGridPosition(TOP_LEFT);
    // moveToGridPosition(BOTTOM_RIGHT);
    // moveToGridPosition(BOTTOM_LEFT);
    // steppersResetToHome(); // bottom left
    // holderNextPosition();
}

void loop()
{
    // String color0 = colorSensors.readColor(0);
    // String color1 = colorSensors.readColor(1);
    // String color2 = colorSensors.readColor(2);

    // or for full debug output:
    // debugChannel(0);
    // debugChannel(1);
    // Serial.println("============");
    // colorSensors.debugChannel(2);
    // Serial.print(digitalRead(SWITCH_HOR));
    // Serial.print(" ");
    // Serial.println(digitalRead(SWITCH_VER));

    delay(300);
    // linefollowWithFive(FORWARD);

    // steppersMoveToPosition(-200, -200);
    // delay(100);
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
    // printSensorVal(leftSensor);
    // delay(100);
    // printEncoders();
    // Serial.println(digitalRead(SWITCH_HOR));
}