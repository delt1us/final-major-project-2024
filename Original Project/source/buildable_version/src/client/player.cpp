/*
 * @Author: Armin Raad <armin3600z@gmail.com>
 * @Date: 2024-03-08 10:04:51
 * @Last Modified by: Armin Raad <armin3600z@gmail.com>
 * @Last Modified time: 2024-04-19 16:57:03
 */

#include "player.h"
#include "raylib.h"
#include "clock.h"

Player::Player(const char *path) {
  position.x = 0.0f;
  position.y = 0.0f;

  sprite = LoadTexture(path);
}

Player::~Player() { UnloadTexture(sprite); }

void Player::Update() { UpdateLocation(); }

void Player::Draw() {
  DrawTexture(sprite, position.x - sprite.width / 2.0f,
              position.y - sprite.height / 2.0f, WHITE);
}

// Called every frame from Update()
void Player::UpdateLocation() {
  if (IsKeyDown(KEY_RIGHT)) {
    position.x += speed * Clock::deltaTime;
  }
  if (IsKeyDown(KEY_LEFT)) {
    position.x -= speed * Clock::deltaTime;
  }
  if (IsKeyDown(KEY_UP)) {
    position.y -= speed * Clock::deltaTime;
  }
  if (IsKeyDown(KEY_DOWN)) {
    position.y += speed * Clock::deltaTime;
  }
}
