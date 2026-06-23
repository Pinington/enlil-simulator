#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "ParticleSystem.h"

class Engine {
private:
    ParticleSystem particles;
public:
    Engine(ParticleSystem particles) : particles(std::move(particles)) {}
};

#endif