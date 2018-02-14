#ifndef RASTERIZEVERTEX_H
#define RASTERIZEVERTEX_H

#include "RasterizerMode.h"
#include "Project.h"
#include <glm/glm.hpp>

namespace rtr {

class RasterizeVertex : public RasterizerMode {

    private:
    REALTIME_API void DrawVertex(const Object&, const glm::mat4&, Device&,
                                 const Project&) const;
    public:
    REALTIME_API void operator()(const Object&, const glm::mat4&, Device&, 
                                 const Project&) const;
};

}
#endif