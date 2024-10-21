/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:29:41
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-06-08 23:15:02
 */

#pragma once

#include "json.hpp"
#include "tile.h"
#include <memory>
#include <raylib.h>
#include <stack>
#include <unordered_map>
#include <vector>

class Tileset {
public:
  std::unordered_map<int, Tile> tileMap;

  ~Tileset();
  void LoadTileset(int firstgid, const char *filepath);

  std::vector<int> GetSpawnpointTileIds();

private:
  std::vector<int> spawnpointTileIds;

  std::stack<std::shared_ptr<Texture2D>> textureStack;

  void LoadTiles(int firstgid, const nlohmann::json &data);
  void AddPropertiesToTile(const nlohmann::json &tileObjects, int firstgid);
  void AddObjectsToTile(const nlohmann::json &tileObjects, int firstgid);
  void LoadSpritesheet(const char *filepath, const nlohmann::json &data);
};
