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
    void addParticles(std::vector<std::unique_ptr<Particle>>&& particles);
    void updateSystem();
};

#endif