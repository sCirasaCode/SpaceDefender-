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
    acceleration = raylib::Vector2{0, 0};
    accelerationRate = PLAYER_ACCELERATION_RATE;
    rotation = 90.0f; // rotation to adjust Texture to the right direction
}


void Player::Move() {
    if (!active) return;

    acceleration = raylib::Vector2{0, 0};

    if (IsKeyDown(KEY_D)) acceleration.x += accelerationRate;
    if (IsKeyDown(KEY_A)) acceleration.x -= accelerationRate;
    if (IsKeyDown(KEY_S)) acceleration.y += accelerationRate;
    if (IsKeyDown(KEY_W)) acceleration.y -= accelerationRate;

    velocity = CalcVelocity(velocity, acceleration);
    
    position += velocity;
    position.x = Clamp(position.x, 0.0f+radius, SCREEN_WIDTH  - radius-10);
    position.y = Clamp(position.y, 0.0f+radius, SCREEN_HEIGHT - radius-10);
    
}

raylib::Vector2 Player::CalcVelocity(raylib::Vector2 velocity, raylib::Vector2 acceleration) const {
    velocity += acceleration;

    // Using Physics drag to slow down the player
    // global constant for all entities
    velocity *= DRAG;
    
    if (velocity.Length() > speed){
    velocity = velocity.Normalize() * speed;
    }

    return velocity;
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

