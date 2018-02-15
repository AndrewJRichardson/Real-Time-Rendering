#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "Real-Time-Rendering.h"

using namespace rtr;

//Globals, TODO: remove if possible, globals are bad
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 600;

bool init				(SDL_Window** window, SDL_Surface** windowSurface);
bool loadMedia			(SDL_Surface** surface);
void close				(SDL_Window** window);
int  fpsCounter			();
void renderText			(std::string text, TTF_Font* font, SDL_Surface** surface,
						 SDL_Color textColour, SDL_Color backgroundColour);
void RegisterController (int ContId, SDL_GameController** controller);

//SDL requires this main signature for multi platform compatibility
int main(int argc, char* args[]) {

	const int SCREEN_WIDTH  = 800;
	const int SCREEN_HEIGHT = 600;
	int delay = 0;
		
	
	//The window to render to
	SDL_Window* window = NULL;

	//Surfaces that the window will contain
	//a surface is just an image, it can be drawn to.
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* textSurface   = NULL;

	//Load a mesh from a .obj file
	ObjectParser p = ObjectParser();
	Mesh*        m = nullptr;
	p.ParseFile("resources/Suz.obj", &m);

	//Create an object, object allows a single mesh to be reused
	Object objA = Object(*m, glm::vec3(0, 0, 0));
	Object objB = Object(*m, glm::vec3(10, 0, -10));



	//Attempt to init the video component of SDL and print an error if it fails
	if (init(&window, &windowSurface)) {

		//Init SDL_ttf and some variables so that FPS text can be rendered
		TTF_Init();
		TTF_Font*			font			 = TTF_OpenFont("resources/PT_Sans.ttf", 12);
		SDL_Color			foregroundColor  = { 255, 255, 255 };
		SDL_Color			backgroundColor  = { 0, 0, 0 };
		SDL_Rect			textLocation	 = { 0, 0, 0, 0 };
		SDL_Surface*		textSurface		 = NULL;
		SDL_GameController* controller		 = NULL;
		int					controllerSwitch = 0;

		SDL_SetWindowGrab		 (window, SDL_TRUE);
		SDL_SetRelativeMouseMode (SDL_TRUE);

		//Create a camera to view the world with
		Camera camera = Camera(glm::vec3(0, 0, -10));
		float camSpeed = 0.2f;


		try {
			//TODO: Replace function pointer with functors?
			//TODO: Better name for device?

			//Create a device to handle the rendering
			Device device			 = { *windowSurface };


			//device.currentRenderMode = &Device::RenderPoints;

			Pipeline pipeline = {RasterizeWireframe(), ViewOrthogonal(), device};
			bool quit = false;
			while (!quit) {
				//device.Clear(camera);
				pipeline.device.Clear(camera);
				SDL_Event event;

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT) {
						quit = true;
					}
					else if (event.type == SDL_CONTROLLERDEVICEADDED) {
						RegisterController(event.cdevice.which, &controller);
					}
					else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
						if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) {
							controllerSwitch++;

							switch (controllerSwitch) {
							// case 0:
							// 	if (device.currentRenderMode != &Device::RenderPoints) {
							// 		device.currentRenderMode = &Device::RenderPoints;
							// 		std::cout << "Render Mode: Point" << std::endl;
							// 	}
							// 	break;
							// case 1:
							// 	if (device.currentRenderMode != &Device::RenderWireframes) {
							// 		device.currentRenderMode = &Device::RenderWireframes;
							// 		std::cout << "Render Mode: Wireframe" << std::endl;
							// 	}
							// 	break;
							// case 2:
							// 	if (device.currentRenderMode != &Device::RenderFill) {
							// 		device.currentRenderMode = &Device::RenderFill;
							// 		std::cout << "Render Mode: Fill" << std::endl;
							// 	}
								controllerSwitch = -1;
								break;
							}
						}

					}
					else if (event.type == SDL_KEYDOWN) {

						switch (event.key.keysym.sym)
						{

						case SDLK_ESCAPE:
							quit = true;
							break;
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
						// case SDLK_1:
						// 	if (device.currentRenderMode != &Device::RenderPoints) {
						// 		device.currentRenderMode = &Device::RenderPoints;
						// 		std::cout << "Render Mode: Point" << std::endl;
						// 	}
						// 	break;
						// case SDLK_2:
						// 	if (device.currentRenderMode != &Device::RenderWireframes) {
						// 		device.currentRenderMode = &Device::RenderWireframes;
						// 		std::cout << "Render Mode: Wireframe" << std::endl;
						// 	}
						// 	break;
						// case SDLK_3:
						// 	if (device.currentRenderMode != &Device::RenderFill) {
						// 		device.currentRenderMode = &Device::RenderFill;
						// 		std::cout << "Render Mode: Fill" << std::endl;
						// 	}
							break;

						case SDLK_w:
							camera.position -= camSpeed * camera.front;
							break;
						case SDLK_s:
							camera.position += camera.front * camSpeed;
							break;
						case SDLK_d:
							camera.position += glm::cross(camera.front, camera.up) * camSpeed;
							break;
						case SDLK_a:
							camera.position -= glm::cross(camera.front, camera.up) * camSpeed;
							break;
						case SDLK_i:
							camera.position = glm::vec3(camera.position.x, camera.position.y + camSpeed, 
														camera.position.z);
							break;
						case SDLK_k:
							camera.position = glm::vec3(camera.position.x, camera.position.y - camSpeed,
														camera.position.z);
							break;

						default:
							break;
						}
					}
					else if (event.type == SDL_MOUSEMOTION) {
						camera.Rotate(-event.motion.xrel, event.motion.yrel);
					}
				}
				if (controller) {
					Sint16 rX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
					Sint16 rY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
					Sint16 lX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					Sint16 lY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

					int deadZone = 3000;

					if (rX > deadZone || rX < -deadZone || rY > deadZone || rY < -deadZone) {
						camera.Rotate(-rX * 0.00001, rY*0.00001);
					}
					if (lY > deadZone || lY < -deadZone) {
						camera.position += camera.front * (float)(lY * 0.000001);
					}if (lX > deadZone || lX < -deadZone) {
						camera.position += glm::cross(camera.front, camera.up) * (float)(lX * 0.000001);
					}
				}

				//Tell device to render an object
				//device.Render(objA);
				pipeline.Render(objA);
				//Update the window with changes
				renderText("FPS: " + std::to_string(fpsCounter()), font, &textSurface, foregroundColor,
						   backgroundColor);
				SDL_BlitSurface(textSurface, NULL, windowSurface, &textLocation);
				SDL_FreeSurface(textSurface);
				SDL_UpdateWindowSurface(window);

				SDL_Delay(delay);
			}
			TTF_CloseFont(font);
		}
		catch (const std::exception & ex) {
			printf(ex.what());
		}


	}
	SDL_FreeSurface(textSurface);
	close(&window);

	return 0;

}





bool init(SDL_Window** window, SDL_Surface** windowSurface) {

	//Attempt to init the video component of SDL and print an error if it fails
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
		printf("SDL did not init! Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		*window = SDL_CreateWindow("SDL Test", 300, 300, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
                                   | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
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


void renderText(std::string text, TTF_Font* font, SDL_Surface** surface, SDL_Color textColour, SDL_Color backgroundColour) {
	*surface = TTF_RenderText_Shaded(font, text.c_str(), textColour, backgroundColour);
}


void close(SDL_Window** window) {
	//Destroy the window
	SDL_DestroyWindow(*window);
	*window = NULL;
	//Quit out of SDL
	SDL_Quit();
}


//TODO: Move to top of file or refactor into funstion somehow
Uint32 framespersecond{ 0 };
Uint32 lastFrameTicks{ 0 };

int fpsCounter() {
	Uint32 currentFrameTicks = SDL_GetTicks();
	Uint32 difference = currentFrameTicks - lastFrameTicks;
	lastFrameTicks = currentFrameTicks;

	if (difference != 0) {
		framespersecond = 1000 / difference;
	}

	//printf("FPS: %lu\n", framespersecond);
	return framespersecond;
}


void RegisterController(int ContId, SDL_GameController** controller) {
	if (SDL_IsGameController(ContId)) {
		*controller = SDL_GameControllerOpen(ContId);
		if (controller) {
			std::cout << "Controller Registered" << std::endl;
		}
	}
}