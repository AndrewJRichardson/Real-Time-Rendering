#include "Mesh.h"

Mesh::Mesh(std::string name, int vertCount, int faceCount) {
	this->name = name;
	vertices = new glm::vec3[vertCount];
	faces = new Face[faceCount];
	rotation = glm::quat(glm::vec3(0, 0, 0));
}

Mesh::~Mesh() {
	delete[] vertices;
	delete[] faces;
}


