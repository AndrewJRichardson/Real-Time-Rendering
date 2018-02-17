#include "VertexShader.h"

//Default vert shader, just returns unmodified vert
glm::vec3 rtr::VertexShader::operator()(glm::vec3& vert) const {
    return vert;
}