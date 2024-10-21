/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:25:30
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-21 20:08:28
 */

#pragma once

#include "json.hpp"
#include "tileset.h"
#include <raylib.h>
#include <utility>
#include <vector>

struct Layer {
  int id;
  std::vector<std::pair<int, Vector2>> tiles;
};

class Map {
public:
  Map(const char *filepath);
  const void Draw();

private:
  std::vector<Layer> layers;
  Tileset tileset;

  void LoadMap(nlohmann::json data);
  void LoadTilesets(const char *mapFilepath, nlohmann::json data);
};
