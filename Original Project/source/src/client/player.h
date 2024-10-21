/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 10:04:49
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-03-13 12:06:03
 */

#pragma once

#include "raylib.h"

class Player {
public:
  Vector2 position;

  Player(const char *path);
  ~Player();

  void Update();
  void Draw();

private:
  // Position that isn't rounded to 8x8 grid
  Vector2 realPosition;

  float speed = 16.0f;

  Texture2D sprite;

  void UpdateLocation();
};
