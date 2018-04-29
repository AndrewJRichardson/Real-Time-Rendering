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

    /// Processes a mesh for rendering one face at a time
    /**
     * Heart of the renderer, calls all operations for rendering an obect
     * 
     * operations in order:
     * 
     * MVP transform -> Backface culling -> VertexShader -> ViewMode -> 
     * RasterizerMode
     *
     */ 
    class VertexProcessor {

        public:
        ///Creates an MVP matrix (technically PVM due to matrix ordering) for the current object
        /**
         * Creates the transform matrix to take a vertex from object space to view space
         * 
         * As GLM uses column major matrices the operations are performed "backwards" from
         * how they are traditionally described
         * 
         * This is likely to be moved or reworked in the future. Currently vertex processor
         * is creating a transform matrix per face of an object, when only one needs to be
         * created per object per frame. So this can be optimized
         */
        REALTIME_API glm::mat4 CreateMVPMatrix(const Object&, const Device&) const;

        /**
         * Calls all operations for rendering the face of an object
         * operations in order
         * MVP transform -> Backface Culling -> VertexShader -> ViewMode -> 
         * RasterizerMode
         */
        REALTIME_API void operator()(const Object&, const ViewMode&, 
                                     const glm::mat4&,
                                     Device&, const Face&) const;
    };
}


#endif