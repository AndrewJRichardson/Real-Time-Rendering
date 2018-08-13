#include "ViewPerspective.h"

glm::vec3 rtr::ViewPerspective::operator()(glm::vec3& vert) const {
	vert.x /= -vert.z;
	vert.y /= -vert.z;
    return vert;
}