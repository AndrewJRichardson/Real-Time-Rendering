#include "Object.h"


Object::Object(Mesh& mesh, glm::vec3 pos) : mesh(mesh) {
	position = pos;
}


Object::~Object()
{
}
