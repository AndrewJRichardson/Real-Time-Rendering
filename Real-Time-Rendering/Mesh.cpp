#include "Mesh.h"


Mesh::Mesh(const std::string& name, int vertCount, int faceCount) {
	this->name = name;
	vertices = new glm::vec3[vertCount];
	faces = new Face[faceCount];
	this->vertCount = vertCount;
	this->faceCount = faceCount;
}

Mesh::~Mesh() {
	delete[] vertices;
	delete[] faces;
}


