#ifndef MESH_H
#define MESH_H

#include "Exports.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


struct REALTIME_API Face {
	int a;
	int b;
	int c;
};

class Mesh {
public:
	//Members
	std::string name;
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3* vertices;
	Face* faces;

	float rot = 0.0f;

	//Constructors
	REALTIME_API Mesh(std::string name, int vertCount, int faceCount);
	REALTIME_API ~Mesh();
};

#endif // !MESH_H





