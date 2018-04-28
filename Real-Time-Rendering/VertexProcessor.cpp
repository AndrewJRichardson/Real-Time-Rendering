#include "VertexProcessor.h"

glm::mat4 rtr::VertexProcessor::CreateMVPMatrix(const Object& object,
                                                const Device& device) const {
    
    glm::mat4 modelMatrix = glm::translate(glm::mat4(), 
                                object.position);

    return device.perspectiveMatrix * device.viewMatrix * modelMatrix;
}

void rtr::VertexProcessor::operator()(const Object& object,
                                      const ViewMode& viewmode,
                                      RasterizerMode& rasterizer,
                                      const glm::mat4& transformMatrix,
                                      Device& device,
                                      const Face& face) const {

    // glm::vec3 point1 = face.vertSets[0].v; 
    // glm::vec3 point2 = face.vertSets[1].v;
    // glm::vec3 point3 = face.vertSets[2].v;
    // glm::vec3 normal = face.surfaceNormal;
    FaceVertSet point1 = face.vertSets[0]; 
    FaceVertSet point2 = face.vertSets[1];
    FaceVertSet point3 = face.vertSets[2];
    glm::vec3 normal = face.surfaceNormal;


    // float a = ((point1.x * point2.y) - (point1.y * point2.x)) 
    //         + ((point2.x * point3.y) - (point2.y * point3.x))
    //         + ((point3.x * point1.y) - (point3.y * point1.x));
          
    glm::mat4 modelMatrix = glm::translate(glm::mat4(), 
                                object.position);
    glm::mat4 world = device.viewMatrix * modelMatrix; 
    point1.v = device.Project(point1.v, transformMatrix);
    point2.v = device.Project(point2.v, transformMatrix);
    point3.v = device.Project(point3.v, transformMatrix);

    glm::vec3 e1 = point2.v - point1.v;
    glm::vec3 e2 = point3.v - point2.v;
    glm::vec3 norm = glm::cross(e1, e2);
    normal = world * glm::vec4(normal, 1);
    // normal = device.Project(normal, transformMatrix);
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
    normal = viewmode(normal);
 
    point1.v = device.MapToScreen(point1.v);
    point2.v = device.MapToScreen(point2.v);
    point3.v = device.MapToScreen(point3.v);

    RasterizeTextured r{};
    r.Render(point1, point2, point3, device, object);
    
    //rasterizer(point1, point2, point3, device);
}