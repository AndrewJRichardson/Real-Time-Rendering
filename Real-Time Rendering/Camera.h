#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera{
public:
	//Members
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 direction;
	glm::vec3 up;
	glm::fquat dir;

	//Constructors
	REALTIME_API Camera(glm::vec3 positon, glm::vec3 target);
	REALTIME_API ~Camera();
};


#endif // !CAMERA_H



