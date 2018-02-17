#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "VertexShader.h"

namespace rtr {
class Object
{
public:
	const Mesh& 		mesh;
	const VertexShader& vertShader;
	glm::vec3 position;
	REALTIME_API Object(const Mesh&, glm::vec3, const VertexShader&);
	REALTIME_API ~Object();
};

}
#endif // !OBJECT_H



