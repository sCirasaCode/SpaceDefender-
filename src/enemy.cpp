#include "Enemy.hpp"
#include "TextureManager.hpp"

Enemy::Enemy() {
    active = false;
    speed = ENEMY_SPEED;
    radius = ENEMY_RADIUS;
}

void Enemy::Spawn() {
    active = true;
    float y = GetRandomValue(0, GetScreenHeight());
    

    speed = GetRandomValue(ENEMY_SPEED, ENEMY_SPEED*3); // randomize speed
    radius = GetRandomValue(ENEMY_RADIUS, ENEMY_RADIUS*2); // randomize size

}

void Enemy::Move() {
    if (!active) return;

    position += velocity;

    if (position.x < -40 || position.x > GetScreenWidth()+40 ||
        position.y < -40 || position.y > GetScreenHeight()+40) {
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
