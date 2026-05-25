#ifndef SPHERE_H
#define SPHERE_H

#include "const.h"

typedef struct {
    float x;
    float y;
    float z;
} Vec3d;

typedef struct {
    Vec3d dir;
    int magnitude;
} Force;

class Particle {
protected:
    Vec3d position;
    Vec3d speed;
    float mass;

public:
    Particle(Vec3d position, float mass) : position{position}, mass{mass} {};
    virtual void update() = 0;
    virtual void applyForce(Force f) = 0;
    
};

class Sphere : public Particle {
public:
    Sphere(Vec3d position, float mass) : Particle{position, mass} {};
    void update() override;
    void applyForce(Force f) override;
};

#endif