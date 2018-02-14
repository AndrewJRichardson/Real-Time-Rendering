#include "Pipeline.h"


rtr::Pipeline::Pipeline(const RasterizerMode& rasterizer, 
                        const ViewMode& viewmode,
                        Device& device) : device (device),
                        project(Project()),
                        rasterizer(rasterizer),
                        viewmode(viewmode){}

void rtr::Pipeline::Render(const Object& object){
    glm::mat4 modelMatrix      = glm::translate(glm::mat4(), object.mesh.position);
	const glm::mat4 transformMatrix  = device.perspectiveMatrix * device.viewMatrix * modelMatrix;
	rasterizer(object, transformMatrix, device, project);
}