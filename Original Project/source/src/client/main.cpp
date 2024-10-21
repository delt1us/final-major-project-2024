/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-05 06:08:49
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-19 16:56:40
 */

#include "raylib.h"
#include "gameloop.h"
#include "clock.h"

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "grapefruit client [prototype]");

  SetTargetFPS(60);

  Gameloop gameloop;
  // Main game loop
  while (!WindowShouldClose()) {
    // Updates deltatime
    Clock::Update();
    gameloop.Update();

    BeginDrawing();
    gameloop.Draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
