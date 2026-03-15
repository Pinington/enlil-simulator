#include <graphics/Camera.h>

Camera::Camera(float aspectRatio) {
    this->model.rotate(0.0f, 0.0f, 0.0f, 0.0f);
    this->view.translate(0, 0, -2);
    this->projection.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
}

void Camera::chPerspective(float aspectRatio) {
    projection.setToIdentity();
    projection.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
}

void Camera::rotate(float x, float y, float z, float deg) {
    this->view.rotate(deg, x, y, z);
}

void Camera::move(float x, float y, float z) {
    this->view.translate(x, y, z);
}

QMatrix4x4 Camera::getMatrix() {
    return this->projection * this->view * this->model;
}