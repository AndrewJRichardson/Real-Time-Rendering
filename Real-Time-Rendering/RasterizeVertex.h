#ifndef RASTERIZEVERTEX_H
#define RASTERIZEVERTEX_H

#include "RasterizerMode.h"
#include "Project.h"
#include <glm/glm.hpp>

namespace rtr {

class RasterizeVertex : public RasterizerMode {

    private:
    REALTIME_API void DrawVertex(Device&, glm::vec3& vert) const;
    public:
    REALTIME_API void operator()(Device&, glm::vec3& vert) const;
};

}
#endif