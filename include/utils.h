#ifndef UTILS_H
#define UTILS_H

// Useful structs for core (reused by engine)

typedef struct {
    float x;
    float y;
    float z;
} Vec3d;

typedef struct {
    Vec3d dir;
    int magnitude;
} Force;

#endif