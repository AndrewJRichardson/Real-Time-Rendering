#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glm/glm.hpp>
#include "Exports.h"

namespace rtr {
    class VertexShader {
        public:
        REALTIME_API virtual glm::vec3 operator()(glm::vec3&) const;
    };
}

#endif