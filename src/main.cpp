#include "resource_dir.h"
#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "TextureManager.hpp"
#include "Parallax.hpp"
#include "Physics.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <vector>


int main() {
    
    // Initialization
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");
    window.SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);

    TextureManager textureManager;
    textureManager.LoadGameTextures();

    Parallax parallax;

    Physics physics;

    Player player;
    raylib::Vector2 playerPosition(screenWidth / 2, screenHeight / 2);

    std::vector<Bullet> playerBullets;
    int maxBullets = 20;
    for (int i = 0; i < maxBullets; i++) {
        playerBullets.emplace_back();
    }

    std::vector<Enemy> enemies;
    for (int i = 0; i < 1; i++) {
        enemies.emplace_back();
    }

    std::vector<Bullet> enemyBullets;
    int maxEnemyBullets = 20;
    for (int i = 0; i < maxEnemyBullets; i++) {
        enemyBullets.emplace_back();
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
        player.Shoot(playerBullets);

        // Physics
        physics.HandleAsteroidCollision(asteroids);

        // Update
        for (auto& bullet : playerBullets) {
            bullet.Update();
        }

        for (auto& bullet : enemyBullets) {
            bullet.Update();
        }

        for (auto& asteroid : asteroids) {
            if (!asteroid.IsActive()) {
                asteroid.Spawn(player.GetPosition());
            }
        }

        for (auto& asteroid : asteroids) {
            asteroid.Move();
        }

        for (auto& enemy : enemies) {
            if (!enemy.IsActive())
            enemy.Spawn();
        }

        for (auto& enemy : enemies) {
            enemy.Move();
        }

        // Check for hits and spawn new asteroids
        bool asteroidShot = false;
        for (auto& bullet : playerBullets) {
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

        for (auto& enemy : enemies) {
            if (!enemy.IsActive()) continue;

            for (auto& bullet : playerBullets) {
                if (!bullet.IsActive()) continue;

                if (enemy.CheckCollision(bullet.GetPosition(), BULLET_RADIUS)) {
                    bullet.Deactivate();
                    enemy.Deactivate();
                    player.increaseScore(10);
                    break; // stop checking more enemies for this bullet
                }
            }
        }

        for (auto& enemy : enemies) {
            enemy.Shoot(enemyBullets, player.GetPosition());
        }

        for (auto& enemy : enemies) {
            if (!enemy.IsActive()) continue;

            for (auto& bullet : enemyBullets) {
                if (!bullet.IsActive()) continue;

                if (player.CheckCollision(bullet.GetPosition(), BULLET_RADIUS)) {
                    bullet.Deactivate();
                    player.DecreaseHealth(10);
                    break; // stop checking more enemies for this bullet
                }
            }
        }
        
        // Draw
        BeginDrawing();

        parallax.Update();

        player.Draw();

        raylib::DrawText("Score: " + std::to_string(player.GetScore()), 20, 10, 20, textColor);
        raylib::DrawText("Health: " + std::to_string(player.GetHealth()), 20, 30, 20, textColor);

        for (auto& bullet : playerBullets) {
            if (bullet.IsActive()) {
                bullet.Draw();
            }
        }

        for (auto& bullet : enemyBullets) {
            if (bullet.IsActive()) {
                bullet.Draw();
            }
        }

        for (auto& enemy : enemies) {
            enemy.Draw();
        }

        for (auto& asteroid : asteroids) {
            if (asteroid.IsActive()) {
                asteroid.Draw();
            }
        }

        EndDrawing();
    }

    textureManager.UnloadGameTexture();
    return 0;
}

