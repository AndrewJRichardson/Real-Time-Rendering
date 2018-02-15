#ifndef RASTERIZERMODE_H
#define RASTERIZERMODE_H

#include "SDL.h"
#include "Object.h"
#include "glm\gtc\matrix_transform.hpp"
#include "Device.h"
#include "Project.h"
#include "Exports.h"

namespace rtr {

    class RasterizerMode {
        public:
        REALTIME_API virtual void operator()(Device&, glm::vec3&) const = 0;
    }; 
}

#endif
