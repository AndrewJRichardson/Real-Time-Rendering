#include "RasterizeVertex.h"

void rtr::RasterizeVertex::operator()(glm::vec3& point1, glm::vec3& point2,
                                      glm::vec3& point3, Device& device) const{
    if (point1.z >= 0){
        device.DrawPoint(point1, 0xff, 0xff, 0xff);
    }
    if (point2.z >= 0){
        device.DrawPoint(point2, 0xff, 0xff, 0xff);
    }
    if (point3.z >= 0){
        device.DrawPoint(point3, 0xff, 0xff, 0xff);
    }
}
