#include "Object.h"


rtr::Object::Object(const Mesh& mesh, glm::vec3 pos,
					const VertexShader& vertexShader,
					RasterizerMode& ras) 
					: mesh(mesh), vertShader(vertexShader), rasterizer(ras){
	position = pos;
}


rtr::Object::~Object()
{
}
