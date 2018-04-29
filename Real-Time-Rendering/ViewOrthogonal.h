#ifndef VIEWORTHOGONAL_H
#define VIEWORTHOGONAL_H

#include "Exports.h"
#include "ViewMode.h"

namespace rtr {

    ///ViewMode that projects vertexes to give an orthoganol view
    class ViewOrthogonal : public ViewMode {

        public:
        REALTIME_API glm::vec3 operator()(glm::vec3&) const;
    };
}

#endif