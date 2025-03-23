#include "Parallax.hpp"
#include "TextureManager.hpp"

Parallax::Parallax()
    :   backgroundTexture(TextureManager::background1Texture),
        midgroundTexture(TextureManager::background2Texture),
        foregroundTexture(TextureManager::background3Texture),
        scrollingSpace(0),
        scrollingStar(0),
        scrollingPlanet(0) {
}

void Parallax::Update() {
    scrollingSpace -= 0.1f;
    if (scrollingSpace <= -TextureManager::background1Texture.width*2) scrollingSpace = 0;

    scrollingStar -= 0.2f;
    if (scrollingStar <= -TextureManager::background2Texture.width*2) scrollingStar = 0;

    scrollingPlanet -= 1.4f;
    if (scrollingPlanet <= -TextureManager::background3Texture.width*2) scrollingPlanet = 0;

    Draw();
}

void Parallax::Draw() {
    // Clear screen
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);

    // ========================================================================================================
    // Draw background image twice
    // Draw the first instance
    DrawTexturePro(
        backgroundTexture,
        (Rectangle){0, 0, backgroundTexture.width, backgroundTexture.height}, 
        (Rectangle){scrollingSpace, 0, backgroundTexture.width, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
    DrawTexturePro(
        backgroundTexture,
        (Rectangle){0, 0, backgroundTexture.width, backgroundTexture.height}, 
        (Rectangle){scrollingSpace+backgroundTexture.width, 0, backgroundTexture.width, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
            

    // ========================================================================================================
    // Draw midground image twice
    // Draw the first instance
    DrawTexturePro( 
        midgroundTexture, 
        (Rectangle){0,0, midgroundTexture.width, midgroundTexture.height}, 
        (Rectangle){ scrollingStar, 0, midgroundTexture.width * 0.33f, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
    // Draw the second instance
    DrawTexturePro( 
        midgroundTexture, 
        (Rectangle){0,0, midgroundTexture.width, midgroundTexture.height}, 
        (Rectangle){ scrollingStar + midgroundTexture.width*0.33, 0, midgroundTexture.width * 0.33f, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    // ========================================================================================================

    // Draw foreground (3x the screen width) with seamless looping
    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingPlanet, 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingPlanet + foregroundTexture.width/2, 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingPlanet + 4 * (foregroundTexture.width/2), 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
}