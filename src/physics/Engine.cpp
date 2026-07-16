#include "physics/Engine.h"

void Engine::applyGravity() {
    Force f {
        {0.f, -1.f, 0.f}, // direction
        1                 // magnitude
    };
    for (auto& p : particles.getSystem()) {
        p->applyForce(f);
    }
}