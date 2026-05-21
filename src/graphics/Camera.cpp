#include <graphics/Camera.h>

Camera::Camera(float aspectRatio) {
    view.lookAt({3, 1, 3}, {0, 0, 0}, {0, 1, 0});
    projection.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
}

void Camera::chPerspective(float aspectRatio) {
    projection.setToIdentity();
    projection.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
}

void Camera::rotate(float x, float y, float z, float deg) {
    view.rotate(deg, x, y, z);
}

void Camera::move(float x, float y, float z) {
    view.translate(x, y, z);
}

QMatrix4x4 Camera::getMatrix() {
    return projection * view;
}