/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 09:37:54
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-21 21:11:28
 */

#pragma once

#include "raylib.h"
#include <string>

#define MAX_ZOOM 10.0f
#define MIN_ZOOM 0.0f
#define DEFAULT_ZOOM 0.8f;

class FollowCamera {
public:
  Camera2D camera = {0};

  FollowCamera(Vector2 *pTarget);
  ~FollowCamera();

  void Update();

private:
  Vector2 *pTarget;

  std::string zoomDebugText;
};
