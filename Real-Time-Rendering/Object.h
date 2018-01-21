#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"

class Object
{
public:
	const Mesh& mesh;
	glm::vec3 position;
	REALTIME_API Object(Mesh& mesh, glm::vec3 pos);
	REALTIME_API ~Object();
};


#endif // !OBJECT_H



