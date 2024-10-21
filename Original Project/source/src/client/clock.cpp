/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 10:39:51
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-19 16:55:47
 */

#include "clock.h"
#include "raylib.h"

float Clock::deltaTime;
double Clock::previousTime;

void Clock::Update() {
  double currentTime = GetTime();

  // First time this is called Time::previousTime will be 0
  if (previousTime == 0)
    previousTime = GetTime();

  deltaTime = (float)(currentTime - previousTime);
  previousTime = currentTime;
}
