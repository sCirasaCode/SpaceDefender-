#include "Enemy.hpp"
#include "TextureManager.hpp"
#include "Config.hpp"
#include <iostream>

Enemy::Enemy() {
    active = false;
    radius = ENEMY_RADIUS;
    speed = ENEMY_SPEED;
    baseY = GetScreenHeight()/2;
    pathSelector = 0;
}

void Enemy::Spawn() {
    active = true;

    float baseY = GetScreenHeight()/2;
    position = raylib::Vector2{GetScreenWidth()+(ENEMY_RADIUS*2), baseY}; // randomize position

    speed = GetRandomValue(ENEMY_SPEED, ENEMY_SPEED*2); // randomize speed
    pathSelector = GetRandomValue(0, 3);
}

void Enemy::Move() {
    if (!active) return;

    position.x -= speed;
    position.y = baseY + SelectPath(position.x, pathSelector);

    if (position.x < -300 || position.x > GetScreenWidth()+300 ||
        position.y < -300 || position.y > GetScreenHeight()+300) {
        active = false;
    }
}

float Enemy::SelectPath(float position, int expression) {

    switch (expression)
    {
    case 0:
        return sin(position/50) * 100; // sinus wave
        break;
    case 1:
        return cos(position/50) * 100; // cosinus wave
        break;
    case 2:
        return atan(0.01*(position-(GetScreenWidth()/2))) * 100; // linear with horizontal flip in middle
        break;
    case 3:
        return atan(0.01*(position-(GetScreenWidth()/2))) * -100; // linear with inverse horizontal flip in middle
        break;
    }

}

void Enemy::Shoot(std::vector<Bullet>& bullets, raylib::Vector2 playerPosition) {
    if (!active || playerPosition.x > position.x) return;

    int shootChance = 0;

    if (playerPosition.y - position.y < abs(50)) {
        shootChance = GetRandomValue(0, 50);
    } else {
        shootChance = GetRandomValue(0, 600);
    }

    if (shootChance < 2) {
        for (auto& bullet : bullets) {
            if (!bullet.IsActive()) {
                bullet.Fire(position, raylib::Vector2{-1, 0}, raylib::Vector2{-radius, 0});
                break;
            }
        }
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
