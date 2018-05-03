#include "Object.h"


rtr::Object::Object(const Mesh& mesh, glm::vec3 pos,
					const VertexShader& vertexShader,
					RasterizerMode& ras) 
					: mesh(mesh), vertShader(vertexShader), rasterizer(ras){
	position = pos;
	rotationAxis = glm::vec3(0,1,0);
	scale = glm::vec3(1,1,1);
	angle = 0;
}


rtr::Object::~Object()
{
}
