#ifndef CAMERA_H
#define CAMERA_H

#include "Exports.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

/** \brief Real-Time-Rendering (rtr) namespace, all classes of the library are 
 * under this namespace
 */ 
namespace rtr {


	/// Camera class used to capture a view of the world
	/**
	 * All views of the world are from the perspective of a camera.
	 * 
	 * Without a camera nothing will be rendered.
	 */
	class Camera {
	public:
		//Members
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		float     yaw;
		float	  pitch;

		//Constructors and Destructors
		REALTIME_API Camera(glm::vec3 positon);
		REALTIME_API ~Camera();

		//Methods
		///Uses glm::lookat to focus the camera on a point
		/**
		 *  Creates a glm::mat4 that represents the camera looking at a point
		 * 
		 * 	The point is 1 unit in front of the camera
		 * 
		 * 	The result is used in the MVP (or PVM in this case) transformations
		 */
		REALTIME_API glm::mat4 LookAt() const;

		///Rotates the camera
		/**
		 * Rotates the camera by the amount of the yaw and pitch values
		 * 
		 * Rotations are additive 
		 */
		REALTIME_API void	   Rotate(float yaw, float pitch);
	};
}

#endif // !CAMERA_H



