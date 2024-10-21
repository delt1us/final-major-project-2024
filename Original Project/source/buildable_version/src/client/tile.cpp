/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:34:56
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-05-10 20:26:12
 */

#include "tile.h"
#include "raylib.h"
#include <iostream>

Tile::Tile(int id, int width, int height, int left, int top,
           const Texture2D *spriteSheet)
    : id(id), pSpritesheet(spriteSheet) {
  rect.width = width;
  rect.height = height;
  rect.x = left;
  rect.y = top;

  collider = {0, 0, 0, 0};

  // std::cout << "Loaded tile with id: " << id << " with dimensions (" << left
  //           << "," << top << "," << width << "," << height << ")\n";
}

const void Tile::Draw(const Vector2 &position) {
  DrawTextureRec(*pSpritesheet, rect, position, WHITE);
}

void Tile::SetCollider(int left, int top, int width, int height) {
  collider.x = left;
  collider.y = top;
  collider.width = width;
  collider.height = height;

  // std::cout << "Added collider to tile with id: " << id << " with dimensions
  // ("
  //           << collider.x << "," << collider.y << "," << collider.width <<
  //           ","
  //           << collider.height << ")\n";
}
