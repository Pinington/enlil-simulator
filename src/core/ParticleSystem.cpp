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

std::vector<std::unique_ptr<Particle>>& ParticleSystem::getSystem() {
    return system;
}

std::vector<float> ParticleSystem::getPositions() {
    std::vector<float> positions;
    positions.reserve(system.size() * 3);

    for (const auto& p : system) {
        const Vec3d& pos = p->getPosition();

        positions.push_back(pos.x);
        positions.push_back(pos.y);
        positions.push_back(pos.z);
    }

    return positions;
}