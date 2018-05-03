#include "RasterizeFilled.h"

 void rtr::RasterizeFilled::operator()(FaceVertSet pointA, FaceVertSet pointB,
                                       FaceVertSet pointC, Device& device,
                                       const Object& object) {
    
    if (pointA.v.z >= 2 && pointB.v.z >= 2 && pointC.v.z >= 2)
        device.RenderTriangle(pointA.v, pointB.v, pointC.v);

}