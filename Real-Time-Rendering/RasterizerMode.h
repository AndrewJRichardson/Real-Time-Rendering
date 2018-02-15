#ifndef RASTERIZERMODE_H
#define RASTERIZERMODE_H

#include "SDL.h"
#include "Object.h"
#include "glm\gtc\matrix_transform.hpp"
#include "Device.h"
#include "Exports.h"
#include "ViewMode.h"

namespace rtr {

    class RasterizerMode {
        public:
        REALTIME_API virtual void operator()(Device&, const Object&, 
                                             const ViewMode&, const glm::mat4&)
                                             const = 0;
    }; 
}

#endif
