#include "RasterizeFilled.h"

 void rtr::RasterizeFilled::operator()(FaceVertSet pointA, FaceVertSet pointB,
                                       FaceVertSet pointC, Device& device,
                                       const Object& object) {
         if (pointA.v.x > 0 && pointA.v.x < device.bufferWidth &&
			pointB.v.x > 0 && pointB.v.x < device.bufferWidth &&
			pointC.v.x > 0 && pointC.v.x < device.bufferWidth &&
			pointA.v.y > 0 && pointA.v.y < device.bufferHeight &&
			pointB.v.y > 0 && pointB.v.y < device.bufferHeight &&
			pointC.v.y > 0 && pointC.v.y < device.bufferHeight){ 

   
    if (pointA.v.z >= 2 && pointB.v.z >= 2 && pointC.v.z >= 2)
        device.RenderTriangle(pointA.v, pointB.v, pointC.v);
    }
}