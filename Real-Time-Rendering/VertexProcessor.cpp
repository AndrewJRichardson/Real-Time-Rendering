#include "VertexProcessor.h"
#include "glm/gtx/transform.hpp"

glm::mat4 rtr::VertexProcessor::CreateMVPMatrix(const Object& object,
                                                const Device& device) const {
    
    glm::mat4 modelMatrix = 
                                glm::translate(glm::mat4(), 
                                object.position) * glm::rotate(glm::radians(object.angle), object.rotationAxis);

    return device.perspectiveMatrix * device.viewMatrix * modelMatrix;
}

void rtr::VertexProcessor::operator()(const Object& object,
                                      const ViewMode& viewmode,
                                      const glm::mat4& transformMatrix,
                                      Device& device, const Face& face) const {

    FaceVertSet point1 = face.vertSets[0]; 
    FaceVertSet point2 = face.vertSets[1];
    FaceVertSet point3 = face.vertSets[2];

    glm::mat4 modelMatrix = glm::translate(glm::mat4(), object.position);
    glm::mat4 world = device.viewMatrix * modelMatrix; 

    point1.v = device.Project(point1.v, transformMatrix);
    point2.v = device.Project(point2.v, transformMatrix);
    point3.v = device.Project(point3.v, transformMatrix);

    //TODO: Switch to use precalculated normals
    glm::vec3 e1 = point2.v - point1.v;
    glm::vec3 e2 = point3.v - point2.v;
    glm::vec3 norm = glm::cross(e1, e2);


    float angle = glm::dot(norm, point1.v);
    if (angle <= 0){
          return;
    }    

    point1.v = object.vertShader(point1.v);
    point2.v = object.vertShader(point2.v);
    point3.v = object.vertShader(point3.v);

    point1.v = viewmode(point1.v);
    point2.v = viewmode(point2.v);
    point3.v = viewmode(point3.v);
 
    point1.v = device.MapToScreen(point1.v);
    point2.v = device.MapToScreen(point2.v);
    point3.v = device.MapToScreen(point3.v);

    object.rasterizer(point1, point2, point3, device, object);
}