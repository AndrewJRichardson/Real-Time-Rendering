#ifndef VIEWPERSPECTIVE_H
#define VIEWPERSPECTIVE_H

#include "ViewMode.h"
#include "Exports.h"

namespace rtr{
    ///ViewMode for rendering vertexes with a perspective based view
    class ViewPerspective : public ViewMode {
        public:
        REALTIME_API glm::vec3 operator()(glm::vec3&) const;
    };
}

#endif