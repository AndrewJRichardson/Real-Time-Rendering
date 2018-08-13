#ifndef RASTERIZERMODE_H
#define RASTERIZERMODE_H

#include <glm/glm.hpp>
#include "Exports.h"
#include "Device.h"
#include "Mesh.h"
#include "Object.h"

namespace rtr {

    ///Interface class for creating a rasterizer mode
    /**
     * Rasterizer modes define how the transformed vertices of an object
     * get drawn to screen
     * 
     * Rasterizer Modes are attached to objects so that each object can be
     * drawn using a different mode if the user wishes
     * 
     * This is not pixel shader implementation, though you could implement 
     * a pixel shader within a rasterizer mode
     * 
     * Override operator() to create a rasterizer mode
     * 
     * Responsible for ZBuffering - hope to fix this in a later update
     */
    class RasterizerMode {
        public:
        /// Virtual method that is called by vertex processor
        /**
         * Define how objects with this rasterizer mode should be drawn
         * 
         * Each Face vert set contains the information for one vertex of 
         * a triangle in no particular order. Object is the object the 
         * triangle face beongs to. Device gives access to some useful functions
         * for rasterizing as well as the frames current zBuffer
         *  
         */
        REALTIME_API virtual void operator()(FaceVertSet, FaceVertSet, FaceVertSet,
                                             Device&, const Object&) = 0;
    }; 
}

#endif
