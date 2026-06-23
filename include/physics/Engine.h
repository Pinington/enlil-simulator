#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "ParticleSystem.h"

class Engine {
private:
    ParticleSystem& particles;
    bool checkCollisions(Particle& a, Particle& b);
public:
    Engine(ParticleSystem& particles) : particles(particles) {};
    void resolveCollisions();
    void applyGravity();
};

#endif