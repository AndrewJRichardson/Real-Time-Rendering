#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "ViewMode.h"
#include "Exports.h"

namespace rtr{
    class Perspective : public ViewMode {
        public:
        REALTIME_API glm::vec3 operator()(glm::vec4&);
    };
}

#endif