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

class Pipeline {

    private:
    const ViewMode&        viewmode;
    const VertexProcessor& vertexProcessor;
    int                    threadLimit;

    public:
    Device&          device;
    
    REALTIME_API Pipeline(const ViewMode&,
                          Device& device);
    //REALTIME_API ~Pipeline();
    REALTIME_API void Render(const Object&);
    REALTIME_API void RenderThreaded(const Object&);

};

}

#endif