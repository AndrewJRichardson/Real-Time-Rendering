#include "RasterizeVertex.h"
#include <iostream>

void rtr::RasterizeVertex::operator()(Device& device, glm::vec3& vert) const{

    DrawVertex(device, vert);
}

void rtr::RasterizeVertex::DrawVertex(Device& device, glm::vec3& vert) const{

    device.DrawPoint(vert, 0xff, 0xff, 0xff);
}