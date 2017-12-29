#include "Object.h"


Object::Object(Mesh* mesh, glm::vec3 pos)
{
	this->mesh = mesh;
	position = pos;
}


Object::~Object()
{
}
