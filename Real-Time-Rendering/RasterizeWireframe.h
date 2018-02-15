#ifndef RASTERIZEWIREFRAME_H
#define RASTERIZEWIREFRAME_H

#include "RasterizerMode.h"
#include "Exports.h"


namespace rtr {

    class RasterizeWireframe: public RasterizerMode {

        public:
        REALTIME_API void operator()(Device&, const Object&, const ViewMode&,
                                     const glm::mat4&) const;
    };
}


#endif