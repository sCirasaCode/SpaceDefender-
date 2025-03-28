#include "Config.hpp"
#include "raylib-cpp.hpp"
#include "Asteroid.hpp"
#include "TextureManager.hpp"

Asteroid::Asteroid() {
    active = false;
    speed = ASTEROID_SPEED;
    radius = ASTEROID_RADIUS;
    rotationSpeed = ASTEROID_ROTATION_SPEED;
    rotationDirection = 1;
    rotation = 0;
}

void Asteroid::Spawn(raylib::Vector2 playerPosition) {
    active = true;
    float y = GetRandomValue(0, GetScreenHeight());
    float directionMargin = PLAYER_RADIUS*2+radius*2;

    speed = GetRandomValue(ASTEROID_SPEED, ASTEROID_SPEED*3); // randomize speed
    radius = GetRandomValue(ASTEROID_RADIUS, ASTEROID_RADIUS*1.5); // randomize size
    rotationSpeed = GetRandomValue(ASTEROID_ROTATION_SPEED, ASTEROID_ROTATION_SPEED*4); // randomize rotation speed
    rotationDirection = GetRandomValue(0, 1) == 0 ? -1 : 1; // randomize rotation direction


    position = raylib::Vector2{float(GetScreenWidth()) + ASTEROID_MARGIN, y};
    // randomize direction of asteroid to player position
    direction = (playerPosition - position)+raylib::Vector2{0, GetRandomValue(-directionMargin, directionMargin)};
    direction = (direction).Normalize();
    velocity = direction * speed;
}

void Asteroid::CooldownMax() {
    active = false;
}

void Asteroid::Move() {
    if (!active) return;

    position += velocity;
    rotation += rotationSpeed*rotationDirection;
    if (rotation < 0 && rotationDirection ==-1) rotation += 360;
    if (rotation > 360 && rotationDirection == 1) rotation -= 360;

    if (position.x < - ASTEROID_MARGIN*2 || position.x > GetScreenWidth()+40 ||
        position.y < - ASTEROID_MARGIN*2 || position.y > GetScreenHeight()+40) {
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
    DrawTexturePro( TextureManager::asteroidTexture,
        (Rectangle){ 0, 0, TextureManager::asteroidTexture.width, TextureManager::asteroidTexture.height }, 
        (Rectangle){ position.x, position.y, radius*2, radius*2 }, 
        (Vector2){ radius, radius }, 
        rotation, 
        WHITE);
}

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //
bool Asteroid::IsActive() const{
    return active;
}

void Asteroid::Deactivate() {
    active = false;
}

raylib::Vector2 Asteroid::GetPosition() const{
    return position;
}
