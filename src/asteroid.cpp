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
    position = raylib::Vector2{GetScreenWidth()+ASTEROID_MARGIN, GetScreenHeight()/2};
    direction = playerPosition - position;
}

void Asteroid::Update() {
    if (!active) return;
    
    direction = raylib::Vector2(direction).Normalize();
    velocity = direction * speed;
    position += velocity;
    active = true;

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

void Asteroid::Deactivate(bool active) {
    // false = activate, true = deactivate
    this->active = active;
}

raylib::Vector2 Asteroid::GetPosition() const{
    return position;
}
