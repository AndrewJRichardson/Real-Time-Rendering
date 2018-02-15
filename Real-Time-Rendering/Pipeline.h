#ifndef PIPELINE_H
#define PIPELINE_H

#include "Exports.h"
#include "RasterizerMode.h"
#include "ViewMode.h"
#include "Device.h"
#include "Project.h"
#include "Object.h"

namespace rtr {

class Pipeline {

    private:
    RasterizerMode&  rasterizer;
    ViewMode&        viewmode;
    Project&         project;

    public:
    Device&          device;
    REALTIME_API Pipeline(RasterizerMode&, ViewMode&,
                          Device& device);
    //REALTIME_API ~Pipeline();
    REALTIME_API void Render(const Object&);

};

}

#endif