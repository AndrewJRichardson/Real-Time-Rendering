#include "RasterizeWireframe.h"

//? Decide where to place bresenham method
//Renders objects in a wireframe mode (a line is drawn between vertexes)
//Currently uses bresenham line method
void rtr::RasterizeWireframe::operator()(FaceVertSet point1, FaceVertSet point2,
                                         FaceVertSet point3, Device& device,
										 const Object&){

		if (point1.v.z >= 0 && point2.v.z >= 0) {
			device.DrawLineBresenham(point1.v, point2.v);
		}
		if (point2.v.z >= 0 && point3.v.z >= 0) {
			device.DrawLineBresenham(point2.v, point3.v);
		}
		if (point1.v.z >= 0 && point3.v.z >= 0) {
			device.DrawLineBresenham(point3.v, point1.v);
		}
}

