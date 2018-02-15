#ifndef RASTERIZEVERTEX_H
#define RASTERIZEVERTEX_H

#include "RasterizerMode.h"
#include <glm/glm.hpp>

namespace rtr {

class RasterizeVertex : public RasterizerMode {

    private:
    REALTIME_API void DrawVertex(Device&, const Object&, const ViewMode&,
                                 const glm::mat4&) const;

    public:
    REALTIME_API void operator()(Device&, const Object&, const ViewMode&,
                                 const glm::mat4&) const;
};

}


#endif