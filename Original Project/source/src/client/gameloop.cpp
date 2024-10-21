/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 08:41:13
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-05-10 20:31:39
 */

#include "gameloop.h"
#include "debug.h"
#include "followCamera.h"
#include "map.h"
#include "raylib.h"

Gameloop::Gameloop()
    : player(Player(ASSETS_PATH "player.png")),
      camera(FollowCamera(&player.position)),
      map(Map(ASSETS_PATH "tiled/maps/starter_map.json")) {
  player.position = map.GetSpawnpoint();
}

Gameloop::~Gameloop() {}

void Gameloop::Update() {
  player.Update();
  camera.Update();
}

void Gameloop::Draw() {
  ClearBackground(LIGHTGRAY);

  BeginMode2D(camera.camera);

  map.Draw();
  player.Draw();

  EndMode2D();

  Debug::Draw();
}
