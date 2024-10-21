/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 08:41:19
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-21 19:45:33
 */

#pragma once

#include "followCamera.h"
#include "map.h"
#include "player.h"
#include <raylib.h>

class Gameloop {
public:
  Gameloop();
  ~Gameloop();

  void Update();
  void Draw();

private:
  Player player;
  FollowCamera camera;
  Map map;
};
