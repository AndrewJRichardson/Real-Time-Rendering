#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "VertexShader.h"
#include "SDL.h"

namespace rtr {
	class RasterizerMode;
	class RasterizeFilled;

class Object
{
public:
	const Mesh& 		mesh;
	const VertexShader& vertShader;
	RasterizerMode& rasterizer;
	SDL_Surface* texture;
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float angle;

	REALTIME_API Object(const Mesh&, glm::vec3, const VertexShader&,
						RasterizerMode&);

	REALTIME_API ~Object();
};

}
#endif // !OBJECT_H



