#include "RasterizeWireframe.h"

//? Decide where to place bresenham method
//TODO: If time permits figure out a way to reduce dependance on triangles and faces
//Renders objects in a wireframe mode (a line is drawn between vertexes)
//Currently uses bresenham line method
void rtr::RasterizeWireframe::operator()(glm::vec3& point1, glm::vec3& point2,
                                         glm::vec3& point3, Device& device) const {

		if (point1.z >= 0 && point2.z >= 0) {
			device.DrawLineBresenham(point1, point2);
		}
		if (point2.z >= 0 && point3.z >= 0) {
			device.DrawLineBresenham(point2, point3);
		}
		if (point1.z >= 0 && point3.z >= 0) {
			device.DrawLineBresenham(point3, point1);
		}
}

