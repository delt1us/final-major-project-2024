/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:29:41
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-05-10 20:24:24
 */

#pragma once

#include "json.hpp"
#include "tile.h"
#include <raylib.h>
#include <unordered_map>
#include <vector>

class Tileset {
public:
  std::unordered_map<int, Tile> tileMap;

  ~Tileset();
  void LoadTileset(int firstgid, const char *filepath);

private:
  Texture2D texture;

  void LoadSpritesheet(const char *filepath, const nlohmann::json &data);
};
