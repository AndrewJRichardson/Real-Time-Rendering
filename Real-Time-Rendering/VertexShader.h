#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glm/glm.hpp>
#include "Exports.h"

namespace rtr {
    /// Interface class to derive vertex shaders from
    /**
     * A vertex shader allows for per vertex operations to be inserted into the 
     * rendering process
     * 
     * Inheriting from this interface requires a definition for 
     * operator()(glm::vec3&)
     * 
     * Vertex shaders are carried out after the MVP transform but before
     * the view mode(orthogonal, perspective etc) operation
     */
    class VertexShader {
        public:
        /// Viruaal function for implementing a vertex shader
        REALTIME_API virtual glm::vec3 operator()(glm::vec3&) const = 0;
    };
}

#endif