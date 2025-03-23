#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include <vector>

int main() {
    
    // Initialization
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    Player player;
    raylib::Vector2 playerPosition(screenWidth / 2, screenHeight / 2);

    std::vector<Bullet> bullets;
    int maxBullets = 20;
    for (int i = 0; i < maxBullets; i++) {
        bullets.emplace_back(playerPosition, raylib::Vector2(0, 0));
    }

    std::vector<Asteroid> asteroids;

    for (int i = 0; i < 1; i++) {
        asteroids.emplace_back();
    }
    
    SetTargetFPS(60);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {

        // Input
        player.Move();
        player.Shoot(bullets);


        // Update
        for (auto& bullet : bullets) {
            bullet.Update();
        }

        for (auto& asteroid : asteroids) {
            if (!asteroid.IsActive()) {
                asteroid.Spawn(player.GetPosition());
            }
        }
        
        for (auto& asteroid : asteroids) {
            asteroid.Update();
        }
        
        
        bool asteroidShot = false;
        for (auto& bullet : bullets) {
            if (!bullet.IsActive()) continue;

            for (auto& asteroid : asteroids) {
                if (!asteroid.IsActive()) continue;

                if (asteroid.CheckCollision(bullet.GetPosition(), BULLET_RADIUS)) {
                    bullet.Deactivate();
                    asteroid.Deactivate();

                    asteroidShot = true;
                    break; // stop checking more asteroids for this bullet
                }
            }

            if (asteroidShot) break; // stop after one collision
        }

        if (asteroids.size() < MAX_ASTEROIDS && asteroidShot) { // spawn cap at MAX_ASTEROIDS
            Asteroid newAsteroid;
            newAsteroid.Spawn(player.GetPosition());
            asteroids.push_back(newAsteroid);
        }
        

    





        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        player.Draw();

        for (auto& bullet : bullets) {
            if (bullet.IsActive()) {
                bullet.Draw();
            }
        }

        for (auto& asteroid : asteroids) {
            if (asteroid.IsActive()) {
                asteroid.Draw();
            }
        }

        EndDrawing();
    }

    return 0;
}

