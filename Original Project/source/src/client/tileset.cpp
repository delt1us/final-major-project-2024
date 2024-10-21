/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:29:34
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-06-08 23:17:26
 */

#include "tileset.h"
#include "json.hpp"
#include "tile.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <string>

using json = nlohmann::json;

void Tileset::LoadTileset(int firstgid, const char *filepath) {
  json data = json::parse(std::ifstream(filepath));

  LoadTiles(firstgid, data);
  LoadSpritesheet(filepath, data);

  // Go through special tiles and add their objects to the tile
  json tileObjects = data["tiles"];
  AddObjectsToTile(tileObjects, firstgid);
  AddPropertiesToTile(tileObjects, firstgid);
}

Tileset::~Tileset() {
  while (!textureStack.empty()) {
    UnloadTexture(*textureStack.top());
    textureStack.pop();
  }
}

void Tileset::LoadSpritesheet(const char *filepath,
                              const nlohmann::json &data) {
  // Make spritesheet filepath
  // Remove file name from filepath to get cwd
  std::string cwd = filepath;
  cwd.erase(cwd.begin() + cwd.find_last_of("/") + 1, cwd.end());
  // Cast from json to string
  std::string imagePath = data["image"];
  // Attach imagepath to cwd
  imagePath = cwd + imagePath;

  // Load spritesheet
  Texture2D texture = LoadTexture(imagePath.c_str());
  textureStack.push(std::make_shared<Texture2D>(texture));
}

void Tileset::AddObjectsToTile(const nlohmann::json &tileObjects,
                               int firstgid) {
  for (const auto &tileObject : tileObjects) {
    if (!tileObject.contains("objectgroup"))
      return;
    for (const json object : tileObject["objectgroup"]["objects"]) {
      if (object["type"] == "collider") {
        int id = tileObject["id"];
        tileMap.at(id + firstgid)
            .SetCollider(object["x"], object["y"], object["width"],
                         object["height"]);
      }
    }
  }
}

void Tileset::AddPropertiesToTile(const nlohmann::json &tileObjects,
                                  int firstgid) {
  for (const auto &tileObject : tileObjects) {
    if (!tileObject.contains("properties"))
      return;
    for (const auto &property : tileObject["properties"]) {
      if (property["name"] == "spawnpoint") {
        int id = tileObject["id"];
        spawnpointTileIds.push_back(id + firstgid);
      }
    }
  }
}

void Tileset::LoadTiles(int firstgid, const nlohmann::json &data) {
  // These need to be cast to ints or it doesn't compile
  int tileWidth = data["tilewidth"];
  int imageWidth = data["imagewidth"];
  int tileHeight = data["tileheight"];
  int imageHeight = data["imageheight"];

  int nextTileId = firstgid;

  // Parse through data to add each tile to the tileset
  for (int y = 0; y < imageHeight; y += tileHeight) {
    for (int x = 0; x < imageWidth; x += tileWidth) {
      Tile tile(nextTileId, tileWidth, tileHeight, x, y, textureStack.top());
      tileMap.insert_or_assign(nextTileId, tile);
      nextTileId++;
    }
  }
}

std::vector<int> Tileset::GetSpawnpointTileIds() { return spawnpointTileIds; }
