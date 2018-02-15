#include "ViewOrthogonal.h"


glm::vec3 rtr::ViewOrthogonal::operator()(glm::vec3& vert) const {
    vert.z = 0;
    return vert;
}