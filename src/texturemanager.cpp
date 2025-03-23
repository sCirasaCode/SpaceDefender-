#include "TextureManager.hpp"

raylib::Texture2D TextureManager::backgroundTexture;
raylib::Texture2D TextureManager::playerTexture;
raylib::Texture2D TextureManager::bulletTexture;
raylib::Texture2D TextureManager::asteroidTexture;

void TextureManager::LoadGameTextures() {
    backgroundTexture = LoadTexture("resources/background.png");
    playerTexture = LoadTexture("resources/player.png");
    bulletTexture = LoadTexture("resources/bullet.png");
    asteroidTexture = LoadTexture("resources/asteroid.png");
}

void TextureManager::UnloadGameTexture() {
    UnloadTexture(backgroundTexture);
    UnloadTexture(playerTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(asteroidTexture);
}