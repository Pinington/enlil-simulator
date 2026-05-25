#ifndef P_SYSTEM_H
#define P_SYSTEM_H

#include <vector>

#include "core/Particles.h"

#include "const.h"

class ParticleSystem {
private:
    std::vector<Particle> system;
public:
    void addParticles(std::vector<Particle> particles);
    void updateSystem();
};

#endif