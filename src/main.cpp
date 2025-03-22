#include "raylib-cpp.hpp"

int main() {
    
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    raylib::Vector2 playerPosition(screenWidth / 2, screenHeight / 2);
    
    float playerSpeed = 2.0f;

    
    SetTargetFPS(60);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            playerPosition = GetMousePosition();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);
        DrawCircleV(playerPosition, 20, MAROON);
        EndDrawing();
    }

    return 0;
}