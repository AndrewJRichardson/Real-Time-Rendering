#include "RasterizeVertex.h"
#include <iostream>

void rtr::RasterizeVertex::operator()(const Object& object, 
                                      const glm::mat4& transform, 
                                      Device& device,
                                      const Project& project) const{

    DrawVertex(object, transform, device, project);
}

void rtr::RasterizeVertex::DrawVertex(const Object& object,
                                      const glm::mat4& transform,
                                      Device& device,
                                      const Project& project) const{

    for (int i = 0; i < object.mesh.vertCount; i++) {
		glm::vec3 projected = project(object.mesh.vertices[i], transform,
                                      device.bufferHeight, device.bufferWidth,
                                      device.halfHeight, device.halfWidth);

		if (projected.z > 0) {
			device.DrawPoint(projected, 0xff, 0xff, 0xff);
		}
	}
}