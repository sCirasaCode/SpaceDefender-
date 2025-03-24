#include "TextureManager.hpp"

raylib::Texture2D TextureManager::background1Texture;
raylib::Texture2D TextureManager::background2Texture;
raylib::Texture2D TextureManager::background3Texture;
raylib::Texture2D TextureManager::playerTexture;
raylib::Texture2D TextureManager::enemyTexture;
raylib::Texture2D TextureManager::asteroidTexture;

void TextureManager::LoadGameTextures() {
    background1Texture = LoadTexture("resources/space_background.png");
    background2Texture = LoadTexture("resources/star_background.png");
    background3Texture = LoadTexture("resources/planet_background.png");
    playerTexture = LoadTexture("resources/ship.png");
    enemyTexture = LoadTexture("resources/enemy_ship.png");
    asteroidTexture = LoadTexture("resources/asteroid.png");
}

void TextureManager::UnloadGameTexture() {
    UnloadTexture(background1Texture);
    UnloadTexture(background2Texture);
    UnloadTexture(background3Texture);
    UnloadTexture(playerTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(asteroidTexture);
}