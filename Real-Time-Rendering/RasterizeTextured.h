#ifndef RASTERIZE_TEXTURED_H
#define RASTERIZE_TEXTURED_H

#include "Exports.h"
#include "Mesh.h"
#include "Device.h"
#include "Object.h"
#include "RasterizerMode.h"

namespace rtr {

    class RasterizeTextured : public RasterizerMode{

        public:
        REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                     Device&, const Object& object);
    };
}

#endif
