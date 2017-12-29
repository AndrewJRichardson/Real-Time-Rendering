#ifndef DEVICE_H

#include "Exports.h"

#include <math.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Object.h"


class Device {

public:

	//Members
	SDL_Surface* buffer;
	void (Device::*currentRenderMode)(Object& object, glm::mat4& transformMatrix);
	bool colourFlip;
	glm::mat4 viewMatrix;
	glm::mat4 perspectiveMatrix;

	//Consructors
	REALTIME_API Device(SDL_Surface* surface);

	//Methods
	REALTIME_API void		Clear			 (const Camera&);
	REALTIME_API void		ChangePixel		 (int x, int y, Uint32 colour);
	REALTIME_API void		DrawPoint		 (glm::vec2& point, int r, int g, int b);
	REALTIME_API void		DrawLine		 (glm::vec2& start, glm::vec2& end);
	REALTIME_API void		DrawLineBresenham(glm::vec4& start, glm::vec4& end);
	REALTIME_API glm::vec4  Project			 (glm::vec3& vert, glm::mat4& transform);
	REALTIME_API void		Render			 (Object& mesh);
	REALTIME_API void		RenderPoints	 (Object& object, glm::mat4& transformMatrix);
	REALTIME_API void		RenderWireframes (Object&, glm::mat4&);
	REALTIME_API void		DrawScanLine	 (int currentY, glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec2 pointD, int r, int g, int b);
	REALTIME_API float		InverseSlope	 (glm::vec2& start, glm::vec2& end);
	REALTIME_API float		Slope			 (glm::vec2& start, glm::vec2& end);
	REALTIME_API float		Interpolate		 (float min, float max, float gradient);
	REALTIME_API float		Clamp			 (float value, float min = 0, float max = 1);
	REALTIME_API void		DrawTriangle	 (glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC);
	REALTIME_API void		RenderFill		 (Object&, glm::mat4&);

};



#endif // !DEVICE_H




