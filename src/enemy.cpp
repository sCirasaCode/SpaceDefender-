#include "Enemy.hpp"
#include "TextureManager.hpp"

Enemy::Enemy() {
    active = false;
    radius = ENEMY_RADIUS;
    speed = ENEMY_SPEED;
    baseY = GetScreenHeight()/2;
}

void Enemy::Spawn() {
    active = true;

    float baseY = GetScreenHeight()/2;
    position = raylib::Vector2{GetScreenWidth()+(ENEMY_RADIUS*2), baseY}; // randomize position

    speed = GetRandomValue(ENEMY_SPEED, ENEMY_SPEED*2); // randomize speed
}

void Enemy::Move() {
    if (!active) return;

    position.x -= speed;
    position.y = baseY + sin(position.x / 30.0f) * 20.0f + cos(position.x / 30.0f) * 20.0f;

    if (position.x < -300 || position.x > GetScreenWidth()+300 ||
        position.y < -300 || position.y > GetScreenHeight()+300) {
        active = false;
    }
}

bool Enemy::CheckCollision(raylib::Vector2 bulletPosition, float bulletRadius) {
    if (!active) return false;

    if (CheckCollisionCircles(position, radius, bulletPosition, bulletRadius)) {
        return true;
    }
    return false;
}

void Enemy::Draw() {
    if (!active) return;
    DrawTexturePro( TextureManager::enemyTexture,
        (Rectangle){ 0, 0, TextureManager::enemyTexture.width, TextureManager::enemyTexture.height }, 
        (Rectangle){ position.x, position.y, radius*2, radius*2 }, 
        (Vector2){ radius, radius }, 
        -90.0f,
        WHITE);
}

// ================================================================== //
//                      Getter and Setter Methods                     //
// ================================================================== //

bool Enemy::IsActive() const {
    return active;
}

void Enemy::Deactivate() {
    active = false;
}

raylib::Vector2 Enemy::GetPosition() const {
    return position;
}
