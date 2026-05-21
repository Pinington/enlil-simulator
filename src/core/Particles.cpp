#include "core/Particles.h"

void Sphere::update() {
    position.x += speed.x * DELTA_T;
    position.y += speed.y * DELTA_T;
    position.z += speed.z * DELTA_T;
}

void Sphere::applyForce(Force f) {
    speed.x += (f.magnitude * f.dir.x) / mass;
    speed.y += (f.magnitude * f.dir.y) / mass;
    speed.z += (f.magnitude * f.dir.z) / mass;
}