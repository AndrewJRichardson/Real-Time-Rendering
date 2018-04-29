#ifndef RASTERIZEVERTEX_H
#define RASTERIZEVERTEX_H

#include "RasterizerMode.h"
#include <glm/glm.hpp>

namespace rtr {

class RasterizeVertex : public RasterizerMode {

    public:
    REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                 Device&, const Object&);
};

}


#endif