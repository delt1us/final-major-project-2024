/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 10:39:46
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-19 16:55:29
 */

#pragma once

class Clock {
public:
  static float deltaTime;
  static void Update();

private:
  static double previousTime;
};
