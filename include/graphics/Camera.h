#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>

class Camera {
private:
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QMatrix4x4 model;

public:
    Camera(float aspectRatio);
    void chPerspective(float aspectRatio);
    void rotate(float x, float y, float z, float deg);
    void move(float x, float y, float z);
    QMatrix4x4 getMatrix();
    float speed = 0.1f;
};

#endif