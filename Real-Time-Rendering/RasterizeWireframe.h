#ifndef RASTERIZEWIREFRAME_H
#define RASTERIZEWIREFRAME_H

#include "RasterizerMode.h"
#include "Exports.h"
namespace rtr {

    /** \brief RasterizerMode that draws a white line between each vertex of an 
     * objects face
     */
    /**
     * Uses the Bresenham line drawing method from Device
     */
    class RasterizeWireframe: public RasterizerMode {

        public:
        REALTIME_API void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                     Device&, const Object&);
    };
}


#endif