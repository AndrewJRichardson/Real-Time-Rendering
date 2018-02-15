#include "Pipeline.h"


rtr::Pipeline::Pipeline(const RasterizerMode& rasterizer, 
                        const ViewMode& viewmode,
                        Device& device) : device (device),
                        rasterizer(rasterizer),
                        viewmode(viewmode){}


//Renders an object to the buffer
void rtr::Pipeline::Render(const Object& object){

    glm::mat4 modelMatrix            = glm::translate(glm::mat4(), 
                                           object.mesh.position);
	const glm::mat4 transformMatrix  = device.perspectiveMatrix * 
                                           device.viewMatrix * modelMatrix;

    rasterizer(device, object, viewmode, transformMatrix);
    
}