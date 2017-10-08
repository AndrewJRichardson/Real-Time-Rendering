#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera{
public:
	//Members
	glm::vec3 position;
	glm::vec3 target;

	//Constructors
	Camera();
	~Camera();
};


#endif // !CAMERA_H



