#include "RasterizeVertex.h"
#include <iostream>

void rtr::RasterizeVertex::operator()(Device& device, const Object& object,
                                      const ViewMode& viewmode,
                                      const glm::mat4& transformMatrix) const{

    for (int i = 0; i < object.mesh.vertCount; i++){

        glm::vec3 vert = device.Project(object.mesh.vertices[i],
                             transformMatrix);
        vert           = viewmode(vert);

        if (vert.z > 0){
            vert = device.MapToScreen(vert);
            device.DrawPoint(vert, 0xff, 0xff, 0xff);
        }
    }
}
