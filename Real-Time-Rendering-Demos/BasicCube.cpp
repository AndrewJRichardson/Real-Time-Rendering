#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <memory>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "Real-Time-Rendering.h"

//TODO Remove this using declaration and use proper scope resolution
using namespace rtr;

//TODO: Try to clean up this file if time permits
//TODO: Seperate object loading and handling from setting up and rendering code
//Globals, TODO: remove if possible, globals are bad
const int SCREEN_WIDTH	= 800;
const int SCREEN_HEIGHT = 600;

bool init				(SDL_Window** window, SDL_Surface** windowSurface);
bool loadMedia			(SDL_Surface** surface, std::string name);
void close				(SDL_Window** window);
int  fpsCounter			();
void renderText			(std::string text, TTF_Font* font, SDL_Surface** surface,
                         SDL_Color textColour, SDL_Color backgroundColour);
void RegisterController (int ContId, SDL_GameController** controller);

//SDL requires this signature for main
int main(int argc, char* args[]) {

    const int SCREEN_WIDTH  = 800;
    const int SCREEN_HEIGHT = 600;
    int delay = 0;

    std::unique_ptr<float[]> blah = std::make_unique<float[]>(10);        
    //The window to render to
    SDL_Window* window = NULL;

    //Surfaces that the window will contain
    //a surface is just an image, it can be drawn to.
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* textSurface   = NULL;

    //Load a mesh from a .obj file
    ObjectParser p = ObjectParser();
    Mesh*        m = nullptr;
    p.ParseFile("resources/suz.obj", &m);

    //Create an object, object allows a single mesh to be reused
    VertexShader v = {};
    Object objA = Object(*m, glm::vec3(0, 0, 10), v);
    Object objB = Object(*m, glm::vec3(10, 0, 10), v);


    //Attempt to init the video component of SDL and print an error if it fails
    if (init(&window, &windowSurface)) {

        //TODO: These inits should be added to init
        //Init SDL_image for PNGs 
        IMG_Init(IMG_INIT_PNG);
       
        // Init SDL_ttf and some variables so that FPS text can be rendered
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


        //TODO: Don't think this try is needed anyore, test
        try {
            //Create a device to handle the rendering
            Device device		 = { *windowSurface, camera};
            SDL_Surface* objTex = IMG_Load("resources/tex.png");
            objA.texture = objTex;
			objB.texture = objTex;
            if(objTex == nullptr){
                std::cout << "error loading texture: " << IMG_GetError() << std::endl;
            }
            
            //device.currentRenderMode = &Device::RenderPoints;
            RasterizeFilled r(*window);
            Pipeline* pipeline = new Pipeline {r, ViewPerspective(), device};
            bool quit = false;
            while (!quit) {
                //device.Clear(camera);
                (*pipeline).device.Clear();
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
                            
                            //! Fix this once pipeline redesign is finished
                            switch (controllerSwitch) {
                                case 0:
                                    delete pipeline;
                                    // pipeline = new Pipeline{RasterizeVertex{}, ViewPerspective{}, device};
                                    break;
                                case 1:
                                    delete pipeline;
                                    // pipeline = new Pipeline{RasterizeWireframe{}, ViewPerspective{}, device};
                                    break;
                                case 2:
                                    delete pipeline;
                                    pipeline = new Pipeline{RasterizeFilled{}, ViewPerspective{}, device};
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
                        case SDLK_1:
                            delete pipeline;
                            // pipeline = new Pipeline{RasterizeVertex{}, ViewPerspective{}, device};
                            // pipeline.rasterizer = RasterizeVertex();
                            break;
                        case SDLK_2:
                        	delete pipeline;
                            // pipeline = new Pipeline{RasterizeWireframe{}, ViewPerspective{}, device};
                        	break;
                        case SDLK_3:
                        	delete pipeline;
                            pipeline = new Pipeline{RasterizeFilled{}, ViewPerspective{}, device};
                        	break;

                            //TODO; camera class should probably handle these calculations
                        case SDLK_w:
                            device.camera.position -= camSpeed * device.camera.front;
                            break;
                        case SDLK_s:
                            device.camera.position += device.camera.front * camSpeed;
                            break;
                        case SDLK_d:
                            device.camera.position += glm::cross(device.camera.front, device.camera.up) * camSpeed;
                            break;
                        case SDLK_a:
                            device.camera.position -= glm::cross(device.camera.front, device.camera.up) * camSpeed;
                            break;
                        case SDLK_i:
                            device.camera.position = glm::vec3(device.camera.position.x, device.camera.position.y + camSpeed, 
                                                        device.camera.position.z);
                            break;
                        case SDLK_k:
                            device.camera.position = glm::vec3(device.camera.position.x, device.camera.position.y - camSpeed,
                                                        device.camera.position.z);
                            break;

                        default:
                            break;
                        }
                    }
                    else if (event.type == SDL_MOUSEMOTION) {
                        device.camera.Rotate((float)-event.motion.xrel, (float)event.motion.yrel);
                    }
                }
                if (controller) {
                    Sint16 rX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
                    Sint16 rY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
                    Sint16 lX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
                    Sint16 lY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);

                    int deadZone = 3000;

                    if (rX > deadZone || rX < -deadZone || rY > deadZone || rY < -deadZone) {
                        device.camera.Rotate((float)(-rX * 0.00001), (float)(rY*0.00001));
                    }
                    if (lY > deadZone || lY < -deadZone) {
                        device.camera.position += device.camera.front * (float)(lY * 0.000001);
                    }if (lX > deadZone || lX < -deadZone) {
                        device.camera.position += glm::cross(device.camera.front, device.camera.up) * (float)(lX * 0.000001);
                    }
                }

                //Tell device to render an object
                //device.Render(objA);
                // pipeline->Render(objA);
                pipeline->Render(objB);
                //Update the window with changes
                renderText("FPS: " + std::to_string(fpsCounter()), font, &textSurface, foregroundColor,
                         backgroundColor);
                SDL_BlitSurface(textSurface, NULL, windowSurface, &textLocation);
                SDL_FreeSurface(textSurface);
                //SDL_BlitSurface(objTex, NULL, windowSurface, &textLocation);
                SDL_UpdateWindowSurface(window);

                SDL_Delay(delay);
            }
            //TTF_CloseFont(font);
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


bool loadMedia(SDL_Surface** surface, std::string name) {

    *surface = SDL_LoadBMP(name.c_str());

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
    IMG_Quit();
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