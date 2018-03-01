#include "VertexProcessor.h"

glm::mat4 rtr::VertexProcessor::CreateMVPMatrix(const Object& object,
                                                const Device& device) const {
    
    glm::mat4 modelMatrix = glm::translate(glm::mat4(), 
                                object.mesh.position);

    return device.perspectiveMatrix * device.viewMatrix * modelMatrix;
}

void rtr::VertexProcessor::operator()(const Object& object,
                                      const ViewMode& viewmode,
                                      RasterizerMode& rasterizer,
                                      const glm::mat4& transformMatrix,
                                      Device& device,
                                      const Face& face) const {

    glm::vec3 point1 = face.vertSets[0].v; 
    glm::vec3 point2 = face.vertSets[1].v;
    glm::vec3 point3 = face.vertSets[2].v;

    point1 = device.Project(point1, transformMatrix);
    point2 = device.Project(point2, transformMatrix);
    point3 = device.Project(point3, transformMatrix);

    point1 = object.vertShader(point1);
    point2 = object.vertShader(point2);
    point3 = object.vertShader(point3);

    point1 = viewmode(point1);
    point2 = viewmode(point2);
    point3 = viewmode(point3);

    point1 = device.MapToScreen(point1);
    point2 = device.MapToScreen(point2);
    point3 = device.MapToScreen(point3);

    rasterizer(point1, point2, point3, device);
}