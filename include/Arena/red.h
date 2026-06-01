#pragma once
#include "LineFollow.h"

#ifndef _red_h_
#define _red_h_
void redStart()
{
  lineFollowStrips(4, FORWARD);
  leftTurnEncoder(300);
}
#endif //_red_h_