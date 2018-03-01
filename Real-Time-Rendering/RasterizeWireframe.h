#ifndef RASTERIZEWIREFRAME_H
#define RASTERIZEWIREFRAME_H

#include "RasterizerMode.h"
#include "Exports.h"
namespace rtr {

    class RasterizeWireframe: public RasterizerMode {

        public:
        REALTIME_API void operator()(glm::vec3&, glm::vec3&, glm::vec3&,
                                     Device&);
    };
}


#endif