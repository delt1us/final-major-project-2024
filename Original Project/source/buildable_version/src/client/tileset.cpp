/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:29:34
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-05-10 20:25:03
 */

#include "tileset.h"
#include "json.hpp"
#include "tile.h"
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>

using json = nlohmann::json;

void Tileset::LoadTileset(int firstgid, const char *filepath) {
  std::cout << "Attempting to parse file at path: " << filepath << "\n";
  // Load data from file
  json data = json::parse(std::ifstream(filepath));
  std::cout << "Completed parsing file at path: " << filepath << "\n";

  LoadSpritesheet(filepath, data);

  // These need to be cast to ints or it doesn't compile
  int tileWidth = data["tilewidth"];
  int imageWidth = data["imagewidth"];
  int tileHeight = data["tileheight"];
  int imageHeight = data["imageheight"];

  int nextTileId = firstgid;

  // Parse through data to add each tile to the tileset
  for (int y = 0; y < imageHeight; y += tileHeight) {
    for (int x = 0; x < imageWidth; x += tileWidth) {
      Tile tile(nextTileId, tileWidth, tileHeight, x, y, &texture);
      tileMap.insert_or_assign(nextTileId, tile);
      nextTileId++;
    }
  }

  // Go through special tiles and add their objects to the tile
  json tileObjects = data["tiles"];
  for (const auto &tileObject : tileObjects) {
    for (const json object : tileObject["objectgroup"]["objects"]) {
      if (object["type"] == "collider") {
        tileMap.at(tileObject["id"])
            .SetCollider(object["x"], object["y"], object["width"],
                         object["height"]);
      }
    }
  }
}

Tileset::~Tileset() { UnloadTexture(texture); }

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
  texture = LoadTexture(imagePath.c_str());
}
