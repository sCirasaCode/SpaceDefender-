#include "Parallax.hpp"
#include "TextureManager.hpp"
#include "Config.hpp"

Parallax::Parallax()
    :   backgroundTexture(TextureManager::background1Texture),
        midgroundTexture(TextureManager::background2Texture),
        foregroundTexture(TextureManager::background3Texture),
        scrollingBack(0),
        scrollingMid(0),
        scrollingFore(0) {
}

void Parallax::Update() {
    scrollingBack -= PARALLAX_SPEED_BACKGROUND;
    if (scrollingBack <= -TextureManager::background1Texture.width*2) scrollingBack = 0;

    scrollingMid -= PARALLAX_SPEED_MIDGROUND;
    if (scrollingMid <= -TextureManager::background2Texture.width*2) scrollingMid = 0;

    scrollingFore -= PARALLAX_SPEED_FOREGROUND;
    if (scrollingFore <= -TextureManager::background3Texture.width*2) scrollingFore = 0;

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
        (Rectangle){scrollingBack, 0, backgroundTexture.width, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
    DrawTexturePro(
        backgroundTexture,
        (Rectangle){0, 0, backgroundTexture.width, backgroundTexture.height}, 
        (Rectangle){scrollingBack+backgroundTexture.width, 0, backgroundTexture.width, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
            

    // ========================================================================================================
    // Draw midground image twice
    // Draw the first instance
    DrawTexturePro( 
        midgroundTexture, 
        (Rectangle){0,0, midgroundTexture.width, midgroundTexture.height}, 
        (Rectangle){ scrollingMid, 0, midgroundTexture.width * 0.33f, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
    // Draw the second instance
    DrawTexturePro( 
        midgroundTexture, 
        (Rectangle){0,0, midgroundTexture.width, midgroundTexture.height}, 
        (Rectangle){ scrollingMid + midgroundTexture.width*0.33, 0, midgroundTexture.width * 0.33f, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    // ========================================================================================================

    // Draw foreground (3x the screen width) with seamless looping
    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingFore, 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingFore + foregroundTexture.width/2, 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);

    DrawTexturePro(
        foregroundTexture,
        (Rectangle){0, 0, foregroundTexture.width, foregroundTexture.height}, 
        (Rectangle){scrollingFore + 4 * (foregroundTexture.width/2), 0, foregroundTexture.width/2, SCREEN_HEIGHT},
        (Vector2){0,0},
        0.0f,
        WHITE);
}