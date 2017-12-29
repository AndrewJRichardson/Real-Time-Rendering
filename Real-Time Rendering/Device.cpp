#include "Device.h"
#include <iostream>


//Constructors
Device::Device(SDL_Surface* surface) {
	buffer = surface;
	colourFlip = true;
	perspectiveMatrix = glm::perspective(glm::radians(90.f), (float)buffer->w / buffer->h, 1.f, 100.0f);
}




//Methods

//Creates a transform matrix and calls the currently set render mode
void Device::Render(Object& object) {

	glm::mat4 modelMatrix = glm::translate(glm::mat4(), object.mesh->position);
	glm::mat4 transformMatrix = perspectiveMatrix * viewMatrix * modelMatrix;

	(this->*currentRenderMode) (object, transformMatrix);
}

//Clears the buffer and recreates the viewMatrix
void Device::Clear(const Camera& camera) {
	SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0x00, 0x00, 0x00));
	viewMatrix = camera.LookAt();
}


//Used by Drawpoint to draw into the buffer
//TODO: Remove?
void Device::ChangePixel(int x, int y, Uint32 colour) {
	int index = (x + y * buffer->w);
	Uint32* pixels = (Uint32*)buffer->pixels;

	pixels[index] = colour;
}


//Draws a pixel onto the device buffer
void Device::DrawPoint(glm::vec2& point, int r, int g, int b) {
	if (point.x >= 0 && point.y >= 0 && point.x < buffer->w && point.y < buffer->h) {
		ChangePixel((int)point.x, (int)point.y, SDL_MapRGB(buffer->format, r, g, b));
	}
}


//Projects a vertices into world space and then into clip space
glm::vec4 Device::Project(glm::vec3& vert, glm::mat4& transform) {

	glm::vec4 projected = transform * glm::vec4(vert, 1);
	projected.x /= -projected.w;
	projected.y /= -projected.w;

	projected.x = (projected.x * buffer->w + buffer->w / 2.0f);
	projected.y = (projected.y * buffer->h + buffer->h / 2.0f);

	return projected;
}


//Renders each vertex as a single pixel
void Device::RenderPoints(Object& object, glm::mat4& transformMatrix) {
	for (int i = 0; i < object.mesh->vertCount; i++) {
		glm::vec4 project = Project(object.mesh->vertices[i], transformMatrix);

		if (project.z > 0) {
			DrawPoint(glm::vec2(project.x, project.y), 0xff, 0xff, 0xff);
		}
	}
}


//Draws filled triangles using the scan line method
void Device::DrawScanLine(int currentY, glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC, glm::vec2 pointD, int r, int g, int b) {
	float gradientA = pointA.y != pointB.y ? (currentY - pointA.y) / (pointB.y - pointA.y) : 1;
	float gradientB = pointC.y != pointD.y ? (currentY - pointC.y) / (pointD.y - pointC.y) : 1;

	int sx = (int)Interpolate(pointA.x, pointB.x, gradientA);
	int ex = (int)Interpolate(pointC.x, pointD.x, gradientB);

	for (int x = sx; x < ex; x++) {
		DrawPoint(glm::vec2(x, currentY), r, g, b);
	}
}


//Draws triangles as wireframes
void Device::RenderWireframes(Object& object, glm::mat4& transformMatrix) {
	for (int i = 0; i < object.mesh->faceCount; i++) {
		glm::vec4 point1 = Project(object.mesh->vertices[object.mesh->faces[i].a], transformMatrix);
		glm::vec4 point2 = Project(object.mesh->vertices[object.mesh->faces[i].b], transformMatrix);
		glm::vec4 point3 = Project(object.mesh->vertices[object.mesh->faces[i].c], transformMatrix);

		if (point1.z > 0 && point2.z > 0) {
			DrawLineBresenham(point1, point2);
		}
		if (point2.z > 0 && point3.z > 0) {
			DrawLineBresenham(point2, point3);
		}
		if (point1.z > 0 && point3.z > 0) {
			DrawLineBresenham(point3, point1);
		}

	}
}


//Draws filled triangles
void Device::RenderFill(Object& object, glm::mat4& transformMatrix) {
	for (int i = 0; i < object.mesh->faceCount; i++) {

		glm::vec3 vert1 = object.mesh->vertices[object.mesh->faces[i].a];
		glm::vec3 vert2 = object.mesh->vertices[object.mesh->faces[i].b];
		glm::vec3 vert3 = object.mesh->vertices[object.mesh->faces[i].c];

		glm::vec4 point1 = Project(vert1, transformMatrix);
		glm::vec4 point2 = Project(vert2, transformMatrix);
		glm::vec4 point3 = Project(vert3, transformMatrix);

		/*glm::vec2 point1 = vert1, 1);
		glm::vec2 point2 = transformMatrix * glm::vec4(vert2, 1);
		glm::vec2 point3 = transformMatrix * glm::vec4(vert3, 1);*/

		if (point1.z > 0 && point2.z > 0 && point3.z > 0) {
			DrawTriangle(point1, point2, point3);
		}
	}
}

//Draws lines using the middle point method
void Device::DrawLine(glm::vec2& start, glm::vec2& end) {
	glm::vec2 distance = end - start;

	if (glm::length(distance) < 2) {
		return;
	}

	glm::vec2 middle = start + distance / 2.f;

	DrawPoint(middle, 0xff, 0xff, 0xff);
	DrawLine(start, middle);
	DrawLine(end, middle);
}


//Draws filled triangles using the draw scanline method
void Device::DrawTriangle(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointC) {

	int r, g, b;
	if (colourFlip) {
		r = 0xff;
		g = 0xff;
		b = 0xff;
	}
	else {
		r = 0xff;
		g = 0x00;
		b = 0x00;
	}

	if (pointA.y > pointB.y) {
		glm::vec2 tPoint = pointB;
		pointB = pointA;
		pointA = tPoint;
	}

	if (pointB.y > pointC.y) {
		glm::vec2 tPoint = pointC;
		pointC = pointB;
		pointB = tPoint;
	}

	if (pointA.y > pointB.y) {
		glm::vec2 tPoint = pointB;
		pointB = pointA;
		pointA = tPoint;
	}

	float invAB, invAC;

	if (pointB.y - pointA.y > 0) {
		invAB = InverseSlope(pointA, pointB);
	}
	else {
		invAB = 0;
	}

	if (pointC.y - pointA.y > 0) {
		invAC = InverseSlope(pointA, pointC);
	}
	else {
		invAC = 0;
	}

	bool right = false;
	bool left = false;

	if (pointB.y - pointA.y > 0) {
		invAB = InverseSlope(pointA, pointB);
	}
	else if (pointB.x > pointA.x) {
		right = true;
	}
	else {
		left = true;
	}

	if (right || (!left && invAB > invAC)) {
		for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {
			if (y < pointB.y) {
				DrawScanLine(y, pointA, pointC, pointA, pointB, r, g, b);
			}
			else {
				DrawScanLine(y, pointA, pointC, pointB, pointC, r, g, b);
			}
		}
	}
	else {
		for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {
			if (y < pointB.y) {
				DrawScanLine(y, pointA, pointB, pointA, pointC, r, g, b);
			}
			else {
				DrawScanLine(y, pointB, pointC, pointA, pointC, r, g, b);
			}
		}
	}
	colourFlip = !colourFlip;

}

void Device::DrawLineBresenham(glm::vec4& start, glm::vec4& end) {

	int x = (int)start.x; //Store both values of both vectors
	int y = (int)start.y; //so we don't have to cast them repeatedly in the following loop 
	int ex = (int)end.x;
	int ey = (int)end.y;

	int dx = std::abs((int)end.x - (int)start.x);
	int dy = std::abs((int)end.y - (int)start.y);

	int error = dx - dy; //error is used to determine which pixel we draw too

	int ix; //used to store the values we will increment/decrement the error by
	int iy; //increment and decrement is based on which direction the line is going

	if (x < end.x) {
		ix = 1;
	}
	else {
		ix = -1;
	}

	if (y < end.y) {
		iy = 1;
	}
	else {
		iy = -1;
	}


	bool complete = false;

	while (!complete) {
		DrawPoint(glm::vec2(x, y), 0xff, 0xff, 0xff); //Draw the current point

		if (x == ex && y == ey) { //Exit if the vectors match
			complete = true;
			continue;
		}

		//A difference of 0.5 is used in bresenham's algorithm to determine whether we should move the passive axis along
		//since we are using integers we need to scale the error by 2 to account for the loss of precision
		int tError = error * 2;
		if (tError > -dy) {
			error -= dy;
			x += ix;
		}
		if (tError < dx) {
			error += dx;
			y += iy;
		}
	}

}


float Device::Slope(glm::vec2& start, glm::vec2& end) {
	return (end.y - start.y) / (end.x - end.y);
}


float Device::InverseSlope(glm::vec2& start, glm::vec2& end) {
	return (end.x - start.x) / (end.y - start.y);
}


float Device::Clamp(float value, float min, float max) {
	return std::fmax(min, std::fmin(value, max));
}


float Device::Interpolate(float min, float max, float gradient) {
	return min + (max - min) * Clamp(gradient);
}