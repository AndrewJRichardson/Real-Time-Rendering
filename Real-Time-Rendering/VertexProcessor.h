#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H

#include <glm/glm.hpp>

#include "Exports.h"
#include "Object.h"
#include "Device.h"
#include "RasterizerMode.h"
#include "VertexShader.h"
#include "ViewMode.h"
#include "RasterizeTextured.h"


namespace rtr {

    class VertexProcessor {

        public:
        REALTIME_API glm::mat4 CreateMVPMatrix(const Object&, const Device&) const;
        REALTIME_API void      operator()(const Object&, const ViewMode&, 
                                          RasterizerMode&,
                                          const glm::mat4&,
                                          Device&, const Face&) const;
    };
}


#endif