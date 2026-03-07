#include <graphics/Camera.h>

Camera::Camera(float aspectRatio) {
    this->model.rotate(45.0f, 0, 1, 0);
    this->view.translate(0, 0, -2);
    this->projection.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
}

QMatrix4x4 Camera::getMatrix() {
    return this->projection * this->view * this->model;
}