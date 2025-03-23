#include "Player.hpp"
#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "Bullet.hpp"
#include <vector>
#include "TextureManager.hpp"

Player::Player() {
    active = true;
    position = raylib::Vector2{GetScreenWidth()/2, GetScreenHeight()/2};
    speed = PLAYER_SPEED;
    radius = PLAYER_RADIUS;
    rotation = 90.0f; // rotation to adjust Texture to the right direction
}


void Player::Move() {
    if (!active) return;

    raylib::Vector2 inputDir = {0, 0};

    if (IsKeyDown(KEY_D)) inputDir.x += 1;
    if (IsKeyDown(KEY_A)) inputDir.x -= 1;
    if (IsKeyDown(KEY_S)) inputDir.y += 1;
    if (IsKeyDown(KEY_W)) inputDir.y -= 1;

    if (inputDir.Length() > 0.0f)
        inputDir = inputDir.Normalize();

    position += inputDir * speed;
}


void Player::Shoot(std::vector<Bullet>& bullets) {
    if (!active) return;
    if (IsKeyPressed(KEY_SPACE)) {
        for (auto& bullet : bullets) {
            if (!bullet.IsActive()) {
                bullet.Fire(position);
                break;
            }
        }
    }
}

bool Player::CheckCollision(raylib::Vector2 asteroidPosition, float asteroidRadius) {
    if (!active) return false;

    if (CheckCollisionCircles(position, radius, asteroidPosition, asteroidRadius)) {
        return true;
    }
    return false;
}

void Player::Draw() {
    if (!active) return;
    DrawTexturePro( TextureManager::playerTexture,
        (Rectangle){ 0, 0, TextureManager::playerTexture.width, TextureManager::playerTexture.height }, 
        (Rectangle){ position.x, position.y, radius*2, radius*2 }, 
        (Vector2){ radius, radius }, 
        rotation, 
        WHITE);
}

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //

bool Player::IsActive() const{
    return active;
}

void Player::Deactivate(bool active) {
    this->active = active;
}

raylib::Vector2 Player::GetPosition() const{
    return position;
}

