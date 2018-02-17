#ifndef RASTERIZEFILLED_H
#define RASTERIZEFILLED_H

#include <glm/glm.hpp>

#include "RasterizerMode.h"
#include "Device.h"
#include "Exports.h"

namespace rtr {

    class RasterizeFilled : public RasterizerMode {

        public:
        REALTIME_API void operator()(glm::vec3&, glm::vec3&, glm::vec3&,
                                     Device&) const;
    };
}

#endif