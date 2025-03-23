#include "Player.hpp"
#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "Bullet.hpp"
#include <vector>

Player::Player() {
    active = true;
    position = raylib::Vector2{GetScreenWidth()/2, GetScreenHeight()/2};
    speed = PLAYER_SPEED;
    radius = PLAYER_RADIUS;
}


void Player::Draw() {
    if (!active) return;
    DrawCircleV(position, radius, BLUE);
}

void Player::Move() {
    if (!active) return;
    if (IsKeyDown(KEY_D)) {
        position.x += speed;
    }
    if (IsKeyDown(KEY_A)) {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_W)) {
        position.y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        position.y += speed;
    }
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

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //

bool Player::IsActive() const{
    return active;
}

void Player::Deactivate(bool active) {
    // false = activate, true = deactivate
    this->active = active;
}

raylib::Vector2 Player::GetPosition() const{
    return position;
}

