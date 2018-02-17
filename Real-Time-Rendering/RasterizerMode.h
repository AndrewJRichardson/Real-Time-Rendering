#ifndef RASTERIZERMODE_H
#define RASTERIZERMODE_H

#include <glm/glm.hpp>
#include "Exports.h"
#include "Device.h"

namespace rtr {

    class RasterizerMode {
        public:
        REALTIME_API virtual void operator()(glm::vec3&, glm::vec3&, glm::vec3&,
                                             Device&) const = 0;
    }; 
}

#endif
