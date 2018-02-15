#include "Pipeline.h"


rtr::Pipeline::Pipeline(RasterizerMode& rasterizer, 
                        ViewMode& viewmode,
                        Device& device) : device (device),
                        project(Project()),
                        rasterizer(rasterizer),
                        viewmode(viewmode){}

void rtr::Pipeline::Render(const Object& object){
    glm::mat4 modelMatrix            = glm::translate(glm::mat4(), object.mesh.position);
	const glm::mat4 transformMatrix  = device.perspectiveMatrix * device.viewMatrix * modelMatrix;

    for (int i = 0; i < object.mesh.vertCount; i++){

        glm::vec4 vert = device.Project(object.mesh.vertices[i], transformMatrix);
        glm::vec3 vertView           = viewmode(vert);
        if (vert.z > 0){
            vertView = device.MapToScreen(vertView);
	        rasterizer(device, vertView);
        }
    }
}