#include "graphics/MeshMaker.h"

SphereData SphereMaker::createSphere(float radius) {
    
    auto evalSphere = [](float u, float v, float r) {
        Point p;
        p.x = cos(u)*sin(v)*r;
        p.y = cos(v)*r;
        p.z = sin(u)*sin(v)*r;

        return p;
    };

    auto addVertex = [&](Point p) {
        // Coordinates
        arr.push_back(p.x);
        arr.push_back(p.y);
        arr.push_back(p.z);

        // Colors
        arr.push_back(0.14);
        arr.push_back(0.43);
        arr.push_back(0.12);

        // Normals are normalized in the fragment shader
        arr.push_back(p.x);
        arr.push_back(p.y);
        arr.push_back(p.z);
    };
    
    int uRes = URES;
    int vRes = VRES;

    float uEnd = 2 * M_PI;
    float vEnd = M_PI;
    float uStep = (uEnd) / uRes;
    float vStep = (vEnd) / vRes;

    int c = arr.size() / 9; 
    for (int u = 0; u < uRes; u++) {
        for (int v = 0; v < vRes; v++) {
            float lng = u * uStep;
            float lat = v * vStep;

            float lngN = (u + 1 == uRes) ? uEnd : (u + 1) * uStep;
            float latN = (v + 1 == vRes) ? vEnd : (v + 1) * vStep;

            Point p0 = evalSphere(lng, lat, radius);
            Point p1 = evalSphere(lng, latN, radius);
            Point p2 = evalSphere(lngN, lat, radius);
            Point p3 = evalSphere(lngN, latN, radius);

            addVertex(p0);
            addVertex(p1);
            addVertex(p2);
            addVertex(p3);
            
            idx.push_back(c + 0);
            idx.push_back(c + 1);
            idx.push_back(c + 2);

            idx.push_back(c + 1);
            idx.push_back(c + 2);
            idx.push_back(c + 3);
            c += 4;
        }
    }

    vertexCount = idx.size();

    return {arr, idx};
}

int SphereMaker::getvertexCount() {
    return vertexCount;
}