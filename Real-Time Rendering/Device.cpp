#include "Device.h"
#include <iostream>



	Device::Device(SDL_Surface* surface) {
		buffer = surface;
	}

	void Device::Clear() {
		SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0x00, 0x00, 0x00));
	}


	void Device::ChangePixel(int x, int y, Uint32 colour) {
		int index = (x + y * buffer->w);
		Uint32* pixels = (Uint32*)buffer->pixels;
		
		pixels[index] = colour;
		pixels[index + 1] = colour;
		pixels[index + 2] = colour;
	}


	void Device::DrawPoint(glm::vec2& point) {
		if (point.x >= 0 && point.y >= 0 && point.x < buffer->w && point.y < buffer->h) {
			ChangePixel(point.x, point.y, SDL_MapRGB(buffer->format, 0xff, 0xff, 0xff));
		}
	}


	void Device::Present() {

		//Update the window with the changes made
		//SDL_UpdateWindowSurface(window);

	}

	glm::vec2 Device::Project(glm::vec2& point) {
		float x = point.x * buffer->w + buffer->w / 2.0f;
		float y = -point.y * buffer->h + buffer->h / 2.0f;

		return glm::vec2(x, y);
	}



	void Device::Render(const Camera& camera, Mesh& mesh) {

		glm::mat4 modelMatrix = glm::rotate(glm::mat4(), mesh.rot, glm::vec3(1, 0, 1));
		glm::mat4 viewMatrix = glm::lookAt(camera.position, camera.target, glm::vec3(0, 1, 0));
		glm::mat4 projectionMatrix = glm::perspective(60.0f, (float)800 / (float)600, 0.1f, 1.0f);

		glm::mat4 transformMatrix = projectionMatrix * viewMatrix * modelMatrix;

	/*	for (int i = 0; i < 12; i++) {

			glm::vec3 vert1 = mesh.vertices[mesh.faces[i].a];
			glm::vec3 vert2 = mesh.vertices[mesh.faces[i].b];
			glm::vec3 vert3 = mesh.vertices[mesh.faces[i].c];

			glm::vec2 point1 = transformMatrix * glm::vec4(vert1, 1);
			glm::vec2 point2 = transformMatrix * glm::vec4(vert2, 1);
			glm::vec2 point3 = transformMatrix * glm::vec4(vert3, 1);


			DrawLine(Project(point1), Project(point2));
			DrawLine(Project(point2), Project(point3));
			DrawLine(Project(point3), Project(point1));
		}*/

		for (int i = 0; i < 8; i++) {
			glm::vec2 point1 = transformMatrix * glm::vec4(mesh.vertices[i], 1);
			DrawPoint(Project(point1));
		}

	}


	void Device::DrawLine(glm::vec2& start, glm::vec2& end) {
		glm::vec2 distance = end - start;

		//std::cout << glm::length(distance) << std::endl;
		if (glm::length(distance) < 2) {
			return;
		}

		glm::vec2 middle =  start + distance/2.f;
		DrawPoint(middle);

		DrawLine(start, middle);
		DrawLine(end, middle);
	}
