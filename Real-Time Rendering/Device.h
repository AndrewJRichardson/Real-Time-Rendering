#ifndef DEVICE_H

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Mesh.h"


class Device {

public:

	//Members
	SDL_Surface* buffer;

	//Consructors
	Device(SDL_Surface* surface);

	//Methods
	void		Clear		();
	void		ChangePixel (int x, int y, Uint32 colour);
	void		DrawPoint	(glm::vec2& point);
	void		DrawLine	(glm::vec2& start, glm::vec2& end);
	void		Present		();
	glm::vec2	Project		(glm::vec2& point); 
	void		Render		(const Camera& camera, Mesh& mesh);

};



#endif // !DEVICE_H




