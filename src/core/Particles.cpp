#include "core/Particles.h"

void SphereParticle::update() {
    speed.x += ((forces.x) / mass) * DELTA_T;
    speed.y += ((forces.y) / mass) * DELTA_T;
    speed.z += ((forces.z) / mass) * DELTA_T;

    position.x += speed.x * DELTA_T;
    position.y += speed.y * DELTA_T;
    position.z += speed.z * DELTA_T;
}

void SphereParticle::applyForce(Force f) {
    forces.x += (f.magnitude * f.dir.x);
    forces.y += (f.magnitude * f.dir.y);
    forces.z += (f.magnitude * f.dir.z);
}

std::unique_ptr<Particle> SphereParticle::clone() const {
    return std::make_unique<SphereParticle>(*this);
}