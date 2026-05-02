#ifndef MESH_MAKER
#define MESH_MAKER

#include <vector>
#include <math.h>

#define URES 32
#define VRES 32

struct Point {
    float x;
    float y;
    float z;
};

typedef struct {
    std::vector<float> arr;
    std::vector<unsigned int> idx;
} SphereData;

class SphereMaker{
public:
    SphereData createSphere(float radius);
    int getvertexCount();

private:
    int vertexCount = 0;
    std::vector<float> arr;
    std::vector<unsigned int> idx;
};

class PlatformMaker{
public:
    void initPlatform(float radius);

private:
    int vertexCount = 0;
    std::vector<float> arr;
    std::vector<unsigned int> idx;
};

#endif