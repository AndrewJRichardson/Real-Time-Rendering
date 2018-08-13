#ifndef PIPELINE_H
#define PIPELINE_H

#include <thread>

#include "Exports.h"
#include "RasterizerMode.h"
#include "VertexProcessor.h"
#include "VertexShader.h"
#include "ViewMode.h"
#include "Device.h"
#include "Object.h"

namespace rtr {

///Class for making a rendering pipeline
/**
 * Is a representation of an abstract rendering pipeline
 * requires a ViewMode and a Device
 */
class Pipeline {

    private:
    const ViewMode&        viewmode;
    int                    threadLimit;

    public:
    VertexProcessor& vertexProcessor;
    Device&          device;
    ///Default Contructor
    REALTIME_API Pipeline(const ViewMode&,
                          Device& device);
    ///Renders the passed in object
    /**
     * Uses the VertexShader and RasterizerMode attached to the object
     */
    REALTIME_API void Render(const Object&);
    ///Renders an object but multi-threads the process
    REALTIME_API void RenderThreaded(const Object&);

};

}

#endif