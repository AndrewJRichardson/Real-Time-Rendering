#ifndef MESH_H
#define MESH_H

#include "Exports.h"

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

#include <SDL.h>


struct REALTIME_API Face {
	int a;
	int b;
	int c;
};

class Mesh {
public:
	//Members
	int vertCount;
	int faceCount;
	std::string name;
	glm::vec3 position;
	glm::vec3* vertices;
	Face* faces;

	float rot = 0.0f;

	//Constructors
	REALTIME_API Mesh(const std::string& name, int vertCount, int faceCount);
	REALTIME_API ~Mesh();
};

#endif // !MESH_H





