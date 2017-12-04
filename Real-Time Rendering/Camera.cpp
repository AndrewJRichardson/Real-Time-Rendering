#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target)
{
	this->position = position;
	this->target = target;
	this->direction = glm::normalize(target - position);
	this->up = glm::vec3(0, 1, 0);
	this->dir = glm::fquat(glm::vec3(0, 0, 0));
}


Camera::~Camera()
{
}
