/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-04-08 09:25:27
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-05-10 20:26:27
 */

#include "map.h"
#include "json.hpp"
#include "tileset.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

using json = nlohmann::json;

Map::Map(const char *filepath) {
  std::cout << "filepath: " << filepath << "\n";
  // Load map from file
  json data = json::parse(std::ifstream(filepath));
  LoadMap(data);
  LoadTilesets(filepath, data);

  // Sort descending based on layer ID
  std::sort(layers.begin(), layers.end(),
            [](Layer a, Layer b) { return a.id > b.id; });
}

const void Map::Draw() {
  for (const Layer &layer : layers) {
    for (const auto &tilePair : layer.tiles) {
      tileset.tileMap.find(tilePair.first)->second.Draw(tilePair.second);
    }
  }
}

void Map::LoadMap(nlohmann::json data) {
  int tileWidth = data["tilewidth"];
  int tileHeight = data["tileheight"];

  for (const auto &layer : data["layers"]) {
    Layer newLayer;
    newLayer.id = layer["id"];

    for (const auto &chunk : layer["chunks"]) {
      int startX = chunk["x"];
      int y = chunk["y"];
      int width = chunk["width"];
      int height = chunk["height"];

      int x = startX;
      std::vector<int> data = chunk["data"];

      for (int tile : data) {
        // If end of line
        if (x == startX + width) {
          y++;
          x = startX;
        }

        // If tile isn't 0, add it to the layer with the coordinates
        if (tile != 0) {
          std::pair tileLocationPair(
              tile, Vector2{(float)x * tileWidth, (float)y * tileHeight});
          newLayer.tiles.emplace_back(tileLocationPair);
          // std::cout << "Added tile with id " << tile << " with location("
          //           << x * tileWidth << "," << y * tileHeight
          //           << ") to layer with id " << newLayer.id << "\n";
        }

        x++;
      }
    }

    layers.emplace_back(newLayer);
  }
}

void Map::LoadTilesets(const char *mapFilepath, json data) {
  for (const auto &tilesetData : data["tilesets"]) {
    // Strip map filename from filepath
    std::string mapDirectory = mapFilepath;
    mapDirectory.erase(mapDirectory.begin() + mapDirectory.find_last_of("/") +
                           1,
                       mapDirectory.end());

    // Cast tilesetData to string
    std::string filepath = tilesetData["source"];
    // Combine paths to find path to tileset
    filepath = mapDirectory + filepath;
    int firstgid = tilesetData["firstgid"];
    tileset.LoadTileset(firstgid, filepath.c_str());
  }
}
