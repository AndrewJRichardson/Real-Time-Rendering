#include "Camera.h"

rtr::Camera::Camera(glm::vec3 position) {
    this->position = position;
    up             = glm::vec3(0, 1, 0);
    front          = glm::vec3(0, 0, -1);
    yaw            = -90.f;
    pitch          = 0;
}

rtr::Camera::~Camera() {}

glm::mat4 rtr::Camera::LookAt() const {
    return glm::lookAt(position, position - front, up);
}

void rtr::Camera::Rotate(float yaw, float pitch) {
    this->yaw += yaw;     // test
    this->pitch += pitch; // test2

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (this->pitch > 89.0f) {
        this->pitch = 89.0f;
    }
    if (this->pitch < -89.0f) {
        this->pitch = -89.0f;
    }

    glm::vec3 frontt;
    frontt.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    frontt.y = sin(glm::radians(this->pitch));
    frontt.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front    = glm::normalize(frontt);
}