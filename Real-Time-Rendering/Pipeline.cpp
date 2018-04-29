#include "Pipeline.h"


rtr::Pipeline::Pipeline(const ViewMode& viewmode,
                        Device& device) : device (device),
                        viewmode(viewmode),
                        vertexProcessor(VertexProcessor{}){ threadLimit = 4;}


//Renders an object to the buffer, uses pased in rasterizer and the
//Objects vert shader, splits the rendering between the thread limit amount
void rtr::Pipeline::RenderThreaded(const Object& object){
    glm::mat4 transformMatrix = vertexProcessor.CreateMVPMatrix(object, device);
    
    int facesPerThread = object.mesh.faceCount / threadLimit;
	int facesRemaining = object.mesh.faceCount % threadLimit;

	std::vector<std::thread> threads(threadLimit);
	int marker = 0;
	for (int i = 0; i < threadLimit; i++) {

		if (i == threadLimit - 1) {
			marker += facesRemaining;
		}

		threads[i] = (std::thread(
            //Lambda function that processes a set of faces
            [&](int count, int begin, const Mesh& mesh) -> void {
       
                int end = begin + count;
                for (int i = begin; i < end; i++){
                    vertexProcessor(object, viewmode, transformMatrix,
                                    device, object.mesh.faces[i]);
                }
            }, facesPerThread, marker, std::ref(object.mesh)));

		marker += facesPerThread;
	}
	 std::for_each(threads.begin(), threads.end(), 
                   []( std::thread& t) { t.join(); });
}


void rtr::Pipeline::Render(const Object& object){
    glm::mat4 transformMatrix = vertexProcessor.CreateMVPMatrix(object, device);
    for (int i = 0; i < object.mesh.faceCount; i++){
            vertexProcessor(object, viewmode, transformMatrix, 
                            device, object.mesh.faces[i]);
    }
}