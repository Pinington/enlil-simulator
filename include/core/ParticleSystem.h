#ifndef P_SYSTEM_H
#define P_SYSTEM_H

#include <vector>
#include <memory>

#include "core/Particles.h"

#include "const.h"

class ParticleSystem {
private:
    std::vector<std::unique_ptr<Particle>> system;
public:
    std::vector<std::unique_ptr<Particle>> getSystem(); // Breaking encapsulation for ver. 0
    void addParticles(std::vector<std::unique_ptr<Particle>>&& particles);
    void addParticles(const Particle& particle);
    void updateSystem();
};

#endif