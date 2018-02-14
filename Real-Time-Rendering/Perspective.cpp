#include "Perspective.h"

glm::vec3 rtr::Perspective::operator()(glm::vec4& vert){
	vert.x /= -vert.w;
	vert.y /= -vert.w;
    return vert;
}