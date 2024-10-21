/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:34:42
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-21 20:53:34
 */

#pragma once

#include "raylib.h"

class Tile {
public:
  Tile(int id, int width, int height, int left, int top,
       const Texture2D *spriteSheet);

  void SetCollider(int left, int top, int width, int height);
  const void Draw(const Vector2 &position);

private:
  int id;
  Rectangle rect;
  // Collider is relative to rect
  Rectangle collider;
  const Texture2D *pSpritesheet;
};
