#ifndef RASTERIZEFILLED_H
#define RASTERIZEFILLED_H

#include <glm/glm.hpp>

#include "RasterizerMode.h"
#include "Device.h"
#include "Exports.h"

namespace rtr {

    ///RasterizerMode that draws a white filled face 
    /**
     * Uses a scanline drawing method from Device
     */
    class RasterizeFilled : public RasterizerMode {

        public:
        REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                     Device&, const Object&);

    };
}

#endif