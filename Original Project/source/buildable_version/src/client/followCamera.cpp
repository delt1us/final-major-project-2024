/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 09:37:51
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-06 18:52:35
 */

#include "followCamera.h"
#include "debug.h"
#include "raylib.h"
#include <string>

FollowCamera::FollowCamera(Vector2 *pTarget) {
  this->pTarget = pTarget;
  camera.zoom = DEFAULT_ZOOM;
  camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  Debug::AddStringToDebugDisplay(&zoomDebugText);
}

FollowCamera::~FollowCamera() {
  Debug::RemoveStringFromDebugDisplay(&zoomDebugText);
}

void FollowCamera::Update() {
  // Follow target if they are in the outer 1/8th of the screen
  Vector2 currentTargetScreenPosition =
      GetWorldToScreen2D(camera.target, camera);
  Vector2 targetScreenPosition = GetWorldToScreen2D(*pTarget, camera);

  // TODO make this easier to read
  // It effectively ensures the player isn't outside a rectangle in the middle
  //  of the screen that is 6/8th the size of the render size
  if (targetScreenPosition.x > 7.0f / 8.0f * GetRenderWidth())
    currentTargetScreenPosition.x =
        targetScreenPosition.x - 3.0f / 8.0f * GetRenderWidth();
  else if (targetScreenPosition.x < 1.0f / 8.0f * GetRenderWidth())
    currentTargetScreenPosition.x =
        targetScreenPosition.x + 3.0f / 8.0f * GetRenderWidth();

  if (targetScreenPosition.y > 7.0f / 8.0f * GetRenderHeight())
    currentTargetScreenPosition.y =
        targetScreenPosition.y - 3.0f / 8.0f * GetRenderHeight();
  else if (targetScreenPosition.y < 1.0f / 8.0f * GetRenderHeight())
    currentTargetScreenPosition.y =
        targetScreenPosition.y + 3.0f / 8.0f * GetRenderHeight();

  camera.target = GetScreenToWorld2D(currentTargetScreenPosition, camera);

  // Zoom
  camera.zoom += (float)GetMouseWheelMove() * 0.05f;

  // Clamp
  if (camera.zoom > MAX_ZOOM)
    camera.zoom = MAX_ZOOM;
  else if (camera.zoom < MIN_ZOOM)
    camera.zoom = MIN_ZOOM;

  // Reset
  if (IsKeyPressed(KEY_R))
    camera.zoom = DEFAULT_ZOOM;

  zoomDebugText = "zoom: " + std::to_string(camera.zoom);
}
