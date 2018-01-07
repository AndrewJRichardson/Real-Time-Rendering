#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rtr {

	class Camera {
	public:

		//Members
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		float     yaw;
		float	  pitch;

		//Constructors
		REALTIME_API Camera(glm::vec3 positon);
		REALTIME_API ~Camera();

		//Methods
		REALTIME_API glm::mat4 LookAt() const;
		REALTIME_API void	   Rotate(float yaw, float pitch);

	};
}

#endif // !CAMERA_H



