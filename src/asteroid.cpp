#include "Asteroid.hpp"
#include "raylib-cpp.hpp"
#include "Config.hpp"

Asteroid::Asteroid() {
    active = false;
    speed = ASTEROID_SPEED;
    radius = ASTEROID_RADIUS;
}

void Asteroid::Spawn(raylib::Vector2 playerPosition) {
    active = true;
    float y = GetRandomValue(0, GetScreenHeight());
    float directionMargin = PLAYER_RADIUS*2+radius*2;

    position = raylib::Vector2{float(GetScreenWidth()) + ASTEROID_MARGIN, y};
    // randomize direction of asteroid to player position
    direction = (playerPosition - position)+raylib::Vector2{0, GetRandomValue(-directionMargin, directionMargin)};
    direction = (direction).Normalize();
    velocity = direction * speed;
}

void Asteroid::Update() {
    if (!active) return;

    position += velocity;

    if (position.x < -40 || position.x > GetScreenWidth()+40 ||
        position.y < -40 || position.y > GetScreenHeight()+40) {
        active = false;
    }
}

bool Asteroid::CheckCollision(raylib::Vector2 bulletPosition, float bulletRadius) {
    if (!active) return false;

    if (CheckCollisionCircles(position, radius, bulletPosition, bulletRadius)) {
        return true;
    }
    return false;
}

void Asteroid::Draw() {
    if (!active) return;
    DrawCircleV(position, radius, MAROON);
}

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //
bool Asteroid::IsActive() const{
    return active;
}

void Asteroid::Deactivate() {
    // false = activate, true = deactivate
    active = false;
}

raylib::Vector2 Asteroid::GetPosition() const{
    return position;
}
