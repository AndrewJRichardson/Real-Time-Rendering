#ifndef OBJECT_H
#define OBJECT_H

#include "Mesh.h"
#include "VertexShader.h"
#include "SDL.h"

namespace rtr {
	class RasterizerMode;
	class RasterizeFilled;

/// Class for storing information regarding an object
/**
 * Holds information for an object that will be rendered
 * 
 * Mesh, VertexShader and RasterizerMode are required, texture is
 * optional.
 *
 * Current rotation method is temporary and cumbersome, to rotate an object
 * speciy the axis you want to rotate with a glm::vec3, for example
 * rotate around Y would be glm::vec3(0,1,0), and set the angle to
 * the amount you wish to rotate around that angle in degrees. Due to the
 * nature of rendering the rotation will be reset each frame, so to create
 * a rotation animation increase the angle by some amount per frame. For example
 * angle = 90; will always produce the same result, it will not rotate the object
 * 90 deg one frame and then a further 90 the next frame. angle+= 90 would be needed 
 * for that 
 * 
 */
class Object
{
public:
	const Mesh& 		mesh;
	const VertexShader& vertShader;
	RasterizerMode& rasterizer;
	SDL_Surface* texture;
	glm::vec3 position;
	glm::vec3 rotationAxis;
	float angle;

	//TODO: make rasterizerMode const so it can be passed
	//rvalue refernces

	///Default contructor
	/**
	 * Sets rotation axis to glm::vec3(0,1,0) and angle to 0
	 */
	REALTIME_API Object(const Mesh&, glm::vec3, const VertexShader&,
						RasterizerMode&);

	//Destructor
	/**
	 * Currently serves no purpose
	 */
	REALTIME_API ~Object();
};

}
#endif // !OBJECT_H



