#include <SDL.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <math.h>
#include <string>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Device.h"



//Globals, TODO: remove, globals are bad
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


bool init(SDL_Window** window, SDL_Surface** windowSurface);
bool loadMedia(SDL_Surface** surface);
void close(SDL_Window** window);
void fpsCounter();



//SDL requires this main signature for multi platform compatibility
int main(int argc, char* args[]) {

	int delay = 0;
	//The window to render to
	SDL_Window* window = NULL;

	//Surface that the window will contain
	//a surface is just an image, it can be drawn to.
	SDL_Surface* windowSurface = NULL;

	SDL_Surface* helloWorld = NULL;


	Mesh m = Mesh("Cube", 8, 12);
	m.position = glm::vec3(0, 0, 500.f);

	m.vertices[0] = glm::vec3(-1, 1, 1);
	m.vertices[1] = glm::vec3(1, 1, 1);
	m.vertices[2] = glm::vec3(-1, -1, 1);
	m.vertices[3] = glm::vec3(1, -1, 1);
	m.vertices[4] = glm::vec3(-1, 1, -1);
	m.vertices[5] = glm::vec3(1, 1, -1);
	m.vertices[6] = glm::vec3(1, -1, -1);
	m.vertices[7] = glm::vec3(-1, -1, -1);

	m.faces[0] = Face{ 0, 1, 2 };
	m.faces[1] = Face{ 1, 2, 3 };
	m.faces[2] = Face{ 1, 3, 6 };
	m.faces[3] = Face{ 1, 5, 6 };
	m.faces[4] = Face{ 0, 1, 4 };
	m.faces[5] = Face{ 1, 4, 5 };

	m.faces[6] = Face{ 2, 3, 7 };
	m.faces[7] = Face{ 3, 6, 7 };
	m.faces[8] = Face{ 0, 2, 7 };
	m.faces[9] = Face{ 0, 4, 7 };
	m.faces[10] = Face{ 4, 5, 6 };
	m.faces[11] = Face{ 4, 6, 7 };

	int mousePrevX = 0;
	int mousePrevY = 0;



	//Attempt to init the video component of SDL and print an error if it fails
	if (init(&window, &windowSurface)) {
		float camSpeed = 0.2f;

		try {
			Device device = Device(windowSurface);
			device.currentRenderMode = &Device::RenderPoints;
			Camera camera = Camera(glm::vec3(0, 0, 500.0f), glm::vec3(0, 0, 530.f));

			bool quit = false;
			while (!quit) {
				device.Clear();
				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					else if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym)
						{
						case SDLK_LEFTBRACKET:
							if (delay > 0) {
								delay -= 1;
								std::cout << "Delay: " << delay << std::endl;
							}
							break;
						case SDLK_RIGHTBRACKET:
							if (delay < 500) {
								delay++;
								std::cout << "Delay: " << delay << std::endl;
							}
							break;
						case SDLK_1:
							if (device.currentRenderMode != &Device::RenderPoints) {
								device.currentRenderMode = &Device::RenderPoints;
								std::cout << "Render Mode: Point" << std::endl;
							}
							break;
						case SDLK_2:
							if (device.currentRenderMode != &Device::RenderWireframes) {
								device.currentRenderMode = &Device::RenderWireframes;
								std::cout << "Render Mode: Wireframe" << std::endl;
							}
							break;
						case SDLK_3:
							if (device.currentRenderMode != &Device::RenderFill) {
								device.currentRenderMode = &Device::RenderFill;
								std::cout << "Render Mode: Fill" << std::endl;
							}
							break;

						case SDLK_w:
							camera.position -= camera.direction * camSpeed;
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;
							//camera.position += (glm::conjugate(camera.dir) * glm::vec3(0.0f, 0.0f, -1.0f) * camSpeed);
							break;
						case SDLK_s:
							//camera.position -= (glm::conjugate(camera.dir) * glm::vec3(0.0f, 0.0f, -1.0f) * camSpeed);

							camera.position += camera.direction * camSpeed;
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;

							break;

						case SDLK_d:
							//camera.position -= (glm::conjugate(camera.dir) * glm::vec3(-1.0f, 0.0f, 0.f) * camSpeed);
							camera.position -= glm::cross(camera.direction, camera.up) * camSpeed;
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;

							break;
						case SDLK_a:
							//camera.position += (glm::conjugate(camera.dir) * glm::vec3(-1.0f, 0.0f, 0.f) * camSpeed);
							camera.position += glm::cross(camera.direction, camera.up) * camSpeed;
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;

							break;

						case SDLK_i:
							camera.position = glm::vec3(camera.position.x, camera.position.y + camSpeed, camera.position.z);
							break;
						case SDLK_k:
							camera.position = glm::vec3(camera.position.x, camera.position.y - camSpeed, camera.position.z);
							break;
						case SDLK_UP:
						{

							/*glm::quat q = glm::angleAxis(glm::radians(1.f), camera.dir * glm::vec3(-1.0f, 0.0f, 0.0f));
							camera.dir = q * camera.dir;*/
						}
						//camera.target = glm::vec3(camera.target.x, camera.target.y + camSpeed, camera.target.z);
						break;
						case SDLK_DOWN:
						{
							glm::quat q = glm::angleAxis(glm::radians(1.f), camera.dir * glm::vec3(1.0f, 0.0f, 0.0f));
							camera.dir = q * camera.dir;
						}
						//camera.target = glm::vec3(camera.target.x, camera.target.y - camSpeed, camera.target.z);
						break;
						case SDLK_LEFT:
						{
							camera.direction = glm::rotate(glm::radians(1.f), camera.up) * glm::vec4(camera.direction, 0);
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;
						}
						break;
						case SDLK_RIGHT:
						{
							camera.direction = glm::rotate(glm::radians(-1.f), camera.up) * glm::vec4(camera.direction, 0);
							camera.direction = glm::normalize(camera.direction);
							camera.target = camera.direction + camera.position;
						}
						//camera.target = glm::vec3(camera.target.x + camSpeed, camera.target.y, camera.target.z);
						break;

						default:
							break;
						}
					}
					else if (event.type == SDL_MOUSEMOTION) {

						camera.direction = glm::rotate(glm::radians((float)-event.motion.xrel), camera.up) * glm::vec4(camera.direction, 0);
						camera.direction = glm::rotate(glm::radians((float)-event.motion.yrel), glm::cross(camera.direction, camera.up)) * glm::vec4(camera.direction, 0);
						camera.direction = glm::normalize(camera.direction);
						std::cout << camera.direction.x << " : " << camera.direction.y << " : " << camera.direction.z << std::endl;
						camera.target = camera.direction + camera.position;


						/*glm::quat x = glm::angleAxis(glm::radians((float)event.motion.xrel), camera.dir * glm::vec3(0.0f, 1.0f, 0.0f));
						glm::quat y = glm::angleAxis(glm::radians((float)event.motion.yrel), camera.dir * glm::vec3(1.0f, 0.0f, 0.0f));*/
						//camera.dir = camera.dir * x;
						//camera.dir = y * camera.dir;


					}

				}

				if (m.rot > 10000) {
					m.rot = 0;
				}
				//m.rot += 0.1f;

				device.Render(camera, m);
				//Update the window with changes
				SDL_UpdateWindowSurface(window);
				//fpsCounter();

				SDL_Delay(delay);
			}
		}
		catch (const std::exception & ex) {
			printf(ex.what());
		}


	}

	SDL_FreeSurface(helloWorld);

	close(&window);

	return 0;

}





bool init(SDL_Window** window, SDL_Surface** windowSurface) {

	//Attempt to init the video component of SDL and print an error if it fails
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL did not init! Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		*window = SDL_CreateWindow("SDL Test", 300, 300, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL) {
			printf("SDL window error! Error: %s\n", SDL_GetError());
			return false;
		}
		*windowSurface = SDL_GetWindowSurface(*window);
		return true;
	}
}



bool loadMedia(SDL_Surface** surface) {

	*surface = SDL_LoadBMP("media/hello.bmp");

	if (*surface == NULL) {
		printf("SDL could not load surface! Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}



void close(SDL_Window** window) {


	//Destroy the window
	SDL_DestroyWindow(*window);
	*window = NULL;


	//Quit out of SDL
	SDL_Quit();
}



Uint32 framespersecond{ 0 };
Uint32 lastFrameTicks{ 0 };

void fpsCounter() {
	Uint32 currentFrameTicks = SDL_GetTicks();
	Uint32 difference = currentFrameTicks - lastFrameTicks;
	lastFrameTicks = currentFrameTicks;

	if (difference != 0) {
		framespersecond = 1000 / difference;
	}

	printf("FPS: %lu\n", framespersecond);
}


