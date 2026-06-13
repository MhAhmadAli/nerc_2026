#pragma once

// First Box direction can change so code is different

#ifndef _red_h_
#define _red_h_

#include <Arduino.h>
#include <LineFollow.h>
#include <ColorSensors.h>

void redStart()
{
  linefollowFiveStrips(3, FORWARD);
  delay(800);
  rightTurnEncoder(200, 180);
  delay(500);
  lineFollowFiveDistance(2.0f, FORWARD);
  delay(100);
  char direction = detectBoxDirection(13, 130);
  if (direction == 'l')
  {
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, BACKWARD);
    linefollowFiveStrips(1, BACKWARD);
    delay(500);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, BACKWARD);
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
    dropPellets();
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(2, FORWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(3, FORWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
  }
  else if (direction == 'r')
  {
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(1, FORWARD);
    delay(500);
    leftTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(1, FORWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
    delay(500);
    linefollowFiveStrips(1, BACKWARD);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
    dropPellets();
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, BACKWARD);
    linefollowFiveStrips(2, BACKWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(5, FORWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
  }
  else
  {
    linefollowFiveStrips(1, BACKWARD);
    delay(800);
    rightTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(1, FORWARD);
    delay(500);
    leftTurnEncoder(200, 180);
    delay(500);
    linefollowFiveEncoder(200, FORWARD);
    linefollowFiveStrips(1, FORWARD);
    delay(800);
    leftTurnEncoder(200, 180);
    delay(500);
    lineFollowFiveDistance(2.0f, FORWARD);
    direction = detectBoxDirection();

    if (direction == 'l')
    {
      linefollowFiveStrips(1, BACKWARD);
      delay(800);
      rightTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, BACKWARD);
      linefollowFiveStrips(1, BACKWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(1, FORWARD);
      delay(800);
      rightTurnEncoder(200, 180);
      delay(500);
      lineFollowFiveDistance(2.0f, FORWARD);
      delay(300);
      linefollowFiveStrips(1, BACKWARD);
      delay(500);
      lineFollowFiveDistance(2.0f, FORWARD);
      dropPellets();
      linefollowFiveStrips(2, BACKWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(4, FORWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      lineFollowFiveDistance(2.0f, FORWARD);
    }
    else if (direction == 'r')
    {
      linefollowFiveStrips(1, BACKWARD);
      delay(800);
      rightTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(1, FORWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(1, FORWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      lineFollowFiveDistance(2.0f, FORWARD);
      delay(300);
      linefollowFiveStrips(1, BACKWARD);
      delay(300);
      lineFollowFiveDistance(2.0f, FORWARD);
      dropPellets();
      linefollowFiveStrips(1, BACKWARD);
      delay(800);
      rightTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(1, FORWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(3, FORWARD);
      delay(800);
      rightTurnEncoder(200, 180);
      delay(500);
      linefollowFiveEncoder(200, FORWARD);
      linefollowFiveStrips(3, FORWARD);
      delay(800);
      leftTurnEncoder(200, 180);
      delay(500);
      lineFollowFiveDistance(2.0f, FORWARD);
      delay(500);
    }
  }

  linefollowFiveStrips(1, BACKWARD);
  delay(500);
  lineFollowFiveDistance(2.0f, FORWARD);
  dropPellets();
  linefollowFiveStrips(1, BACKWARD);
  delay(800);
  leftTurnEncoder(200, 180);
  delay(500);
  linefollowFiveEncoder(200, FORWARD);
  linefollowFiveStrips(2, FORWARD);
  delay(800);
  leftTurnEncoder(200, 180);
  delay(500);
  forwardDistance(20.0f, 110);
  delay(1000);
  lineFollowStrips(1, BACKWARD);
  delay(1000);
  rightTurnEncoder(195, 210);
  delay(1000);
  lineFollowFiveDistance(2.0f);
  delay(500);
  linefollowFiveStrips(1, BACKWARD);
  delay(500);
  lineFollowFiveDistance(2.0f);
  dropPellets();
  backwardEncoder(600);
}
#endif //_red_h_