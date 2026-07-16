#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "utils.h"
#include "const.h"

class Particle {
protected:
    Vec3d position;
    Vec3d speed;
    Vec3d forces;
    float mass;

public:
    Particle(Vec3d position, float mass) : position{position}, mass{mass} {};
    virtual void update() = 0;
    virtual void applyForce(Force f) = 0;
    virtual std::unique_ptr<Particle> clone() const = 0;

    Vec3d getPosition() const { return position; }
};

class SphereParticle : public Particle {
public:
    SphereParticle(Vec3d position, float mass) : Particle{position, mass} {};
    void update() override;
    void applyForce(Force f) override;
    std::unique_ptr<Particle> clone() const override;
};

#endif