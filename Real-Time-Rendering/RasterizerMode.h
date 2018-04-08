#ifndef RASTERIZERMODE_H
#define RASTERIZERMODE_H

#include <glm/glm.hpp>
#include "Exports.h"
#include "Device.h"
#include "Mesh.h"

namespace rtr {

    class RasterizerMode {
        public:
        REALTIME_API virtual void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                             Device&) = 0;
    }; 
}

#endif
