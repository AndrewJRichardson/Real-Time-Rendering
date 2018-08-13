#ifndef RASTERIZE_TEXTURED_H
#define RASTERIZE_TEXTURED_H

#include "Exports.h"
#include "Mesh.h"
#include "Device.h"
#include "Object.h"
#include "RasterizerMode.h"

namespace rtr {

    ///RasterizerMode that draws filled textured triangles
    /**
     * Uses the texture attached to the object, relies on the mesh 
     * having UVs
     * 
     * Uses scan line draw texture from Device
     */
    class RasterizeTextured : public RasterizerMode{

        public:
        REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                     Device&, const Object& object);
    };
}

#endif
