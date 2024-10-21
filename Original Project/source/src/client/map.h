/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:25:30
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-06-08 22:47:53
 */

#pragma once

#include "json.hpp"
#include "tileset.h"
#include <raylib.h>
#include <utility>
#include <vector>

struct Layer {
  int id;
  // pair<id, location>
  std::vector<std::pair<int, Vector2>> tiles;
  bool visible;
};

class Map {
public:
  Map(const char *filepath);
  const void Draw();
  const Vector2 GetSpawnpoint();

private:
  std::vector<Layer> layers;
  Tileset tileset;

  void LoadMap(nlohmann::json data);
  void LoadTilesets(const char *mapFilepath, nlohmann::json data);
  // Can return null when tile is not present
  const std::pair<int, Vector2> *GetFirstTileWithId(int id);
};
