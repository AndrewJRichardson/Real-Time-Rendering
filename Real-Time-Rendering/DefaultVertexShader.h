#ifndef DEFAULTVERTEXSHADER_H
#define DEFAULTVERTEXSHADER_H

#include "VertexShader.h"

namespace rtr{

///Default vertex shader, returns the vertex unmodified
/**
 * Use this shader if you dont want to apply any per vertex
 * operations of your own.
 */
class DefaultVertexShader : public VertexShader {
    ///Returns the vertex unmodified
    REALTIME_API glm::vec3 operator()(glm::vec3&) const;
};


}



#endif