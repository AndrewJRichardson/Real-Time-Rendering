#ifndef RASTERIZE_TEXTURED_H
#define RASTERIZE_TEXTURED_H

#include "Exports.h"
#include "Mesh.h"
#include "Device.h"
#include "Object.h"

namespace rtr {

    class RasterizeTextured{

        public:
        REALTIME_API void Render(FaceVertSet a, FaceVertSet b, FaceVertSet c,
                                 Device& device, const Object& object);

    };
}

#endif
