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
    const RasterizerMode&  rasterizer;
    const ViewMode&        viewmode;
    const Project&         project;

    public:
    Device&          device;
    REALTIME_API Pipeline(const RasterizerMode&, const ViewMode&,
                          Device& device);
    //REALTIME_API ~Pipeline();
    REALTIME_API void Render(const Object&);

};

}

#endif