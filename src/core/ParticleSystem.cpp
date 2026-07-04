#include "core/ParticleSystem.h"

void ParticleSystem::addParticles(std::vector<std::unique_ptr<Particle>>&& particles) {
    if (system.size() + particles.size() > MAX_PARTICLES)
    return;

    system.insert(
        system.end(),
        std::make_move_iterator(particles.begin()),
        std::make_move_iterator(particles.end())
    );
}

void ParticleSystem::addParticles(const Particle& particle) {
    system.push_back(particle.clone());
}

void ParticleSystem::updateSystem() {
    for (auto& p : this->system) {
        p->update();
    }
}