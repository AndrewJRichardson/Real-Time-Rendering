#include "Project.h"

glm::vec3 rtr::Project::operator()(const glm::vec3& vert, 
                                   const glm::mat4& transform,
                                   const int bufferHeight,
                                   const int bufferWidth,
                                   const int halfHeight,
                                   const int halfWidth) const {

    return ProjectVert(vert, transform, bufferHeight, bufferWidth, halfHeight,
                       halfWidth);
}

glm::vec3 rtr::Project::ProjectVert(const glm::vec3& vert,
                                    const glm::mat4& transform,
                                    const int bufferHeight,
                                    const int bufferWidth,
                                    const int halfHeight,
                                    const int halfWidth) const {

    glm::vec4 projected = transform * glm::vec4(vert, 1);

	projected.x = (projected.x * bufferWidth  + halfWidth);
	projected.y = (projected.y * bufferHeight + halfHeight);

	return projected;

}