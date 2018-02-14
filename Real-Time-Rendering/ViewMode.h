#ifndef VIEWMODE_H
#define VIEWMODE_H

#include "Exports.h"
#include <glm/glm.hpp>

namespace rtr{

    class ViewMode {
        public:
        REALTIME_API virtual glm::vec3 operator()(glm::vec4& vert) = 0;
    };

}

#endif