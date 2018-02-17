#include "Pipeline.h"


rtr::Pipeline::Pipeline(const RasterizerMode& rasterizer, 
                        const ViewMode& viewmode,
                        Device& device) : device (device),
                        rasterizer(rasterizer),
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
                    glm::vec3 point1 = mesh.vertices[mesh.faces[i].a];
                    glm::vec3 point2 = mesh.vertices[mesh.faces[i].b];
                    glm::vec3 point3 = mesh.vertices[mesh.faces[i].c];

                    vertexProcessor(object, viewmode, rasterizer, transformMatrix,
                                    device, point1, point2, point3);
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
            glm::vec3 point1 = object.mesh.vertices[object.mesh.faces[i].a];
            glm::vec3 point2 = object.mesh.vertices[object.mesh.faces[i].b];
            glm::vec3 point3 = object.mesh.vertices[object.mesh.faces[i].c];

            vertexProcessor(object, viewmode, rasterizer, transformMatrix, 
                            device, point1, point2, point3);
    }
}