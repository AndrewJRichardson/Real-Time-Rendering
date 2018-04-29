#ifndef VIEWMODE_H
#define VIEWMODE_H

#include "Exports.h"
#include <glm/glm.hpp>

namespace rtr{

    ///Interface for creating view types such as orthoganol and perspectve
    class ViewMode {
        public:
        REALTIME_API virtual glm::vec3 operator()(glm::vec3& vert) const = 0;
    };

}

#endif