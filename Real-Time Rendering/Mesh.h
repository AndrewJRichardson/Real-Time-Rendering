#ifndef MESH_H
#define MESH_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>



struct Face {
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
	Mesh(std::string name, int vertCount, int faceCount);
	~Mesh();
};

#endif // !MESH_H





