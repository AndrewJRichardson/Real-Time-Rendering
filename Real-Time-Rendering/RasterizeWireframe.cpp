#include "RasterizeWireframe.h"


void rtr::RasterizeWireframe::operator()(Device& device, const Object& object,
                                         const ViewMode& viewmode,
                                         const glm::mat4& transformMatrix) const {
for (int i = 0; i < object.mesh.faceCount; i++) {
		glm::vec3 point1 = device.Project(
                               object.mesh.vertices[object.mesh.faces[i].a],
                               transformMatrix);
		glm::vec3 point2 = device.Project(
                               object.mesh.vertices[object.mesh.faces[i].b],
                               transformMatrix);
		glm::vec3 point3 = device.Project(
                               object.mesh.vertices[object.mesh.faces[i].c],
                               transformMatrix);

        point1 = viewmode(point1);
        point2 = viewmode(point2);
        point3 = viewmode(point3);

        point1 = device.MapToScreen(point1);
        point2 = device.MapToScreen(point2);
        point3 = device.MapToScreen(point3);

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
}

