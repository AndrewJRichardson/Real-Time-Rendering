#include "RasterizeFilled.h"


void rtr::RasterizeFilled::operator()(glm::vec3& point1, glm::vec3& point2,
                                      glm::vec3& point3, Device& device) const {
    
    device.RenderTriangle(point1, point2, point3);
}