#include "physics/Engine.h"

void Engine::applyGravity() {
    Force f {0.f, -9.f, 0.f};
    for (auto& p : particles.getSystem()) {
        p->applyForce(f);
    }
}