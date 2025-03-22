#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include <vector>

int main() {
    
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    raylib::Vector2 playerPosition(screenWidth / 2, screenHeight / 2);
    float playerSpeed = 2.0f;

    std::vector<Bullet> bullets;
    const int maxBullets = 20;
    for (int i = 0; i < maxBullets; i++) {
        bullets.emplace_back(playerPosition, raylib::Vector2(0, 0));
    }

    std::vector<Asteroid> asteroids;
    const int maxAsteroids = 1;
    for (int i = 0; i < maxAsteroids; i++) {
        asteroids.emplace_back();
    }
    
    SetTargetFPS(60);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& bullet : bullets) {
                if (!bullet.IsActive()) {
                    bullet.Fire(playerPosition);
                    break;
                }
            }
        }

        for (auto& bullet : bullets) {
            bullet.Update();
        }

        for (auto& asteroid : asteroids) {
            if (!asteroid.IsActive()) {
                asteroid.Spawn(playerPosition);
            }
        }

        for (auto& asteroid : asteroids) {
            asteroid.Update();
        }

        for (auto& bullet : bullets) {
            for (auto& asteroid : asteroids) {
                if (asteroid.IsActive() && bullet.IsActive() &&
                    asteroid.CheckCollision(bullet.GetPosition(), BULLET_RADIUS)) {
                    bullet.Deactivate(true);
                    asteroid.Deactivate(true);
                }
            }
        }



        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(playerPosition, 20, MAROON);

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