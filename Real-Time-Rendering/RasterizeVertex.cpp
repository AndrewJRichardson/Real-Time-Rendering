#include "RasterizeVertex.h"

void rtr::RasterizeVertex::operator()(FaceVertSet point1, FaceVertSet point2,
                                      FaceVertSet point3, Device& device,
                                      const Object& object){
    if (point1.v.z >= 0){
        device.DrawPixel(point1.v, 0xff, 0xff, 0xff);
    }
    if (point2.v.z >= 0){
        device.DrawPixel(point2.v, 0xff, 0xff, 0xff);
    }
    if (point3.v.z >= 0){
        device.DrawPixel(point3.v, 0xff, 0xff, 0xff);
    }
}
