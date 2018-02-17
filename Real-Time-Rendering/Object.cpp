#include "Object.h"


rtr::Object::Object(const Mesh& mesh, glm::vec3 pos,
					const VertexShader& vertexShader) 
					: mesh(mesh), vertShader(vertexShader) {
	position = pos;
}


rtr::Object::~Object()
{
}
