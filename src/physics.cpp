#include "Physics.hpp"
#include "raylib-cpp.hpp"
#include "Config.hpp"
#include "Asteroid.hpp"


void Physics::HandleAsteroidCollision(std::vector<Asteroid>& asteroids) {
    for (size_t i = 0; i < asteroids.size(); ++i) {
        if (!asteroids[i].IsActive()) continue;

        for (size_t j = i + 1; j < asteroids.size(); ++j) {
            if (!asteroids[j].IsActive()) continue;

            if (asteroids[i].CheckCollision(asteroids[j].position, asteroids[j].radius)) {

                raylib::Vector2 normal = asteroids[j].position - asteroids[i].position;
                float distance = normal.Length();
                if (distance == 0.0f || distance >= asteroids[i].radius * 2) continue;

                normal = normal.Normalize();

                float repulsionForce = 0.6f;
                
                // Push them apart
                asteroids[i].velocity -= normal * repulsionForce;
                asteroids[j].velocity += normal * repulsionForce;
                
                float overlap = (asteroids[i].radius * 2 - distance-1.0f) / 2.0f;
                // Reposition them so they don't overlap
                asteroids[i].position -= normal * overlap;
                asteroids[j].position += normal * overlap;
            }
        }
    }
}
