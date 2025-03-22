#include "Bullet.hpp"
#include "raylib-cpp.hpp"
#include "Config.hpp"

Bullet::Bullet(raylib::Vector2 position, raylib::Vector2 velocity) {
    active = false;
    speed = BULLET_SPEED;
    radius = BULLET_RADIUS;
}

void Bullet::Fire(raylib::Vector2 position) {
    active = true;
    raylib::Vector2 direction = raylib::Vector2(1, 0);

    this->position = position;
    velocity = direction * speed;
}

void Bullet::Update() {
    if (!active) return;

    position += velocity;

    if (position.x < 0 || position.x > GetScreenWidth() ||
        position.y < 0 || position.y > GetScreenHeight()) {
        active = false;
    }
}

void Bullet::Draw() {
    if (!active) return;
    DrawCircleV(position, 5, RED);
}

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //
bool Bullet::IsActive() const{
    return active;
}

void Bullet::Deactivate(bool active) {
    // false = activate, true = deactivate
    this->active = active;
}

raylib::Vector2 Bullet::GetPosition() const{
    return position;
}