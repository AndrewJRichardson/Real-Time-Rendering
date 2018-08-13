#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

#include "Real-Time-Rendering.h"

// This application is mererly a demo of the real-time rendering library
// It is not part of the library itself

// SDL setup code adapted from this SDL2 tutorial:
// http://lazyfoo.net/tutorials/SDL/
// SDL Frame Rate counter is from:
// http://sdl.beuc.net/sdl.wiki/SDL_Average_FPS_Measurement

// TODO: Try to clean up this file if time permits
// TODO: Seperate object loading and handling from setting up and rendering code
bool init(SDL_Window**, SDL_Surface**, int, int);
bool loadMedia(SDL_Surface**, std::string);
void close(SDL_Window**);
int  fpsCounter();
void renderText(std::string, TTF_Font*, SDL_Surface**, SDL_Color, SDL_Color);
void RegisterController(int, SDL_GameController**);

// SDL requires this signature for main
int main(int argc, char* args[]) {

    std::map<std::string, rtr::Object&> renderQueue{};

    const int SCREEN_WIDTH  = 800;
    const int SCREEN_HEIGHT = 600;

#define FPS_INTERVAL 1.0

    Uint32 fps_lasttime = SDL_GetTicks();
    Uint32 fps_current  = 0;
    Uint32 fps_frames   = 0;

    // The window to render to
    SDL_Window* window = NULL;

    // Surfaces that the window will contain
    // a surface is just an image, it can be drawn to.
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* textSurface   = NULL;

    // Load a mesh from a .obj file
    rtr::ObjectParser p = rtr::ObjectParser();
    rtr::Mesh*        m = nullptr;
    rtr::Mesh*        z = nullptr;
    rtr::Mesh*        y = nullptr;
    p.ParseFile("resources/cube2.obj", &m);
    p.ParseFile("resources/suz.obj", &z);
    p.ParseFile("resources/plane2.obj", &y);

    // Create an object, object allows a single mesh to be reused
    rtr::DefaultVertexShader v = {};
    rtr::RasterizeWireframe  w = {};
    rtr::RasterizeTextured   t = {};
    rtr::RasterizeFilled     f = {};
    rtr::RasterizeVertex     x = {};

    rtr::Object vert = rtr::Object(*m, glm::vec3(-10, 0, 10), v, x);
    rtr::Object wire = rtr::Object(*m, glm::vec3(10, 0, 10), v, w);
    rtr::Object fill = rtr::Object(*m, glm::vec3(0, 0, 10), v, f);
    rtr::Object text = rtr::Object(*m, glm::vec3(20, 0, 10), v, t);
    rtr::Object monw = rtr::Object(*z, glm::vec3(-5, 0, 10), v, w);
    rtr::Object monf = rtr::Object(*z, glm::vec3(5, 0, 10), v, f);
    rtr::Object back = rtr::Object(*y, glm::vec3(0, 0, 40), v, t);
    rtr::Object wall = rtr::Object(*y, glm::vec3(-24, 0, 13), v, t);
    rtr::Object walr = rtr::Object(*y, glm::vec3(26.5, 10, 13), v, t);
    rtr::Object floo = rtr::Object(*y, glm::vec3(6.5, -20, 13), v, t);
    rtr::Object roof = rtr::Object(*y, glm::vec3(-3.5, 30, 13), v, t);

    renderQueue.insert(std::pair<std::string, rtr::Object&>("vert", vert));
    renderQueue.insert(std::pair<std::string, rtr::Object&>("text", text));
    renderQueue.insert(std::pair<std::string, rtr::Object&>("fill", fill));
    renderQueue.insert(std::pair<std::string, rtr::Object&>("wire", wire));

    // Attempt to init the video component of SDL and print an error if it fails
    if (init(&window, &windowSurface, SCREEN_WIDTH, SCREEN_HEIGHT)) {

        // TODO: These inits should be added to init
        IMG_Init(IMG_INIT_PNG); // Init SDL_image for PNGs

        // Init SDL_ttf and some variables so that FPS text can be rendered
        TTF_Init();
        TTF_Font*           font = TTF_OpenFont("resources/PT_Sans.ttf", 12);
        SDL_Color           foregroundColor  = {255, 255, 255};
        SDL_Color           backgroundColor  = {0, 0, 0};
        SDL_Rect            textLocation     = {0, 0, 0, 0};
        SDL_Surface*        textSurface      = NULL;
        SDL_GameController* controller       = NULL;
        int                 controllerSwitch = 0;
        int                 spaceSwitch      = 0;

        SDL_SetWindowGrab(window, SDL_TRUE);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        // Create a camera to view the world with
        rtr::Camera camera   = rtr::Camera(glm::vec3(0, 0, -30));
        float       camSpeed = 0.2f;

        try {
            // Create a device to handle the rendering
            rtr::Device  device = {*windowSurface, camera};
            SDL_Surface* objTex = IMG_Load("resources/btex.png");

            if (objTex == nullptr) {
                std::cout << "error loading texture: " << IMG_GetError()
                          << std::endl;
            }

            text.texture = objTex;
            walr.texture = objTex;
            wall.texture = objTex;
            back.texture = objTex;
            floo.texture = objTex;
            roof.texture = objTex;

            vert.rotationAxis = glm::vec3(1, 1, 0);
            text.rotationAxis = glm::vec3(1, 1, 0);
            fill.rotationAxis = glm::vec3(1, 1, 0);
            wire.rotationAxis = glm::vec3(1, 1, 0);
            monw.rotationAxis = glm::vec3(1, 1, 0);
            monf.rotationAxis = glm::vec3(1, 1, 0);
            back.rotationAxis = glm::vec3(0, 1, 0);
            walr.rotationAxis = glm::vec3(0, 0, 1);
            roof.rotationAxis = glm::vec3(0, 0, 1);
            floo.rotationAxis = glm::vec3(0, 0, 1);
            floo.scale        = glm::vec3(10, 10, 10);
            roof.scale        = glm::vec3(10, 10, 10);
            walr.scale        = glm::vec3(10, 10, 10);
            wall.scale        = glm::vec3(10, 10, 10);
            back.scale        = glm::vec3(10, 10, 10);

            floo.angle += 90;
            roof.angle -= 90;
            back.angle += 90;
            walr.angle += 180;

            rtr::Pipeline* pipeline =
              new rtr::Pipeline{rtr::ViewPerspective(), device};
            bool quit = false;

            while (!quit) {
                text.angle += 0.1f;
                fill.angle += 0.1f;
                wire.angle += 0.1f;
                vert.angle += 0.1f;
                monw.angle += 0.1f;
                monf.angle += 0.1f;

                (*pipeline).device.Clear();
                SDL_Event event;

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        quit = true;

                    } else if (event.type == SDL_CONTROLLERDEVICEADDED) {
                        RegisterController(event.cdevice.which, &controller);

                    } else if (event.type == SDL_CONTROLLERBUTTONDOWN ||
                               (event.type == SDL_KEYDOWN &&
                                event.key.keysym.sym == SDLK_SPACE)) {

                        if (event.cbutton.button ==
                              SDL_CONTROLLER_BUTTON_LEFTSHOULDER ||
                            event.key.keysym.sym == SDLK_SPACE) {

                            controllerSwitch++;

                            switch (controllerSwitch) {

                            case 1:
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("monf",
                                                                       monf));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("monw",
                                                                       monw));

                                renderQueue.erase("text");
                                renderQueue.erase("fill");
                                renderQueue.erase("wire");
                                renderQueue.erase("vert");
                                break;

                            case 2:
                                renderQueue.erase("monw");
                                renderQueue.erase("monf");

                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("back",
                                                                       back));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("wall",
                                                                       wall));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("walr",
                                                                       walr));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("roof",
                                                                       roof));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("floo",
                                                                       floo));
                                camera.position = glm::vec3(0, 0, -40);
                                camera.front    = glm::vec3(0, 0, -1);
                                camera.yaw      = -90;
                                camera.pitch    = 0;
                                break;
                            case 3:
                                renderQueue.erase("back");
                                renderQueue.erase("wall");
                                renderQueue.erase("floo");
                                renderQueue.erase("roof");
                                renderQueue.erase("walr");

                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("text",
                                                                       text));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("wire",
                                                                       wire));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("fill",
                                                                       fill));
                                renderQueue.insert(
                                  std::pair<std::string, rtr::Object&>("vert",
                                                                       vert));
                                controllerSwitch = 0;
                                break;
                            }
                        }
                        if (event.cbutton.button ==
                            SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
                            camera.position = glm::vec3(0, 0, -10);
                            camera.front    = glm::vec3(0, 0, -10);
                            camera.yaw      = -90;
                            camera.pitch    = 0;
                        }
                        if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                            pipeline->vertexProcessor.backface =
                              !pipeline->vertexProcessor.backface;
                        }

                    } else if (event.type == SDL_KEYDOWN) {

                        switch (event.key.keysym.sym) {

                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                            // TODO; camera class should probably handle these
                            // calculations
                        case SDLK_w:
                            device.camera.position -=
                              camSpeed * device.camera.front;
                            break;

                        case SDLK_s:
                            device.camera.position +=
                              device.camera.front * camSpeed;
                            break;

                        case SDLK_d:
                            device.camera.position +=
                              glm::cross(device.camera.front,
                                         device.camera.up) *
                              camSpeed;
                            break;

                        case SDLK_a:
                            device.camera.position -=
                              glm::cross(device.camera.front,
                                         device.camera.up) *
                              camSpeed;
                            break;

                        case SDLK_i:
                            device.camera.position =
                              glm::vec3(device.camera.position.x,
                                        device.camera.position.y + camSpeed,
                                        device.camera.position.z);
                            break;

                        case SDLK_k:
                            device.camera.position =
                              glm::vec3(device.camera.position.x,
                                        device.camera.position.y - camSpeed,
                                        device.camera.position.z);
                            break;

                        case SDLK_r:
                            device.camera.position = glm::vec3(0, 0, -10);
                            device.camera.front    = glm::vec3(0, 0, -1);
                            camera.yaw             = -90;
                            camera.pitch           = 0;
                            break;
                        case SDLK_b:
                            pipeline->vertexProcessor.backface =
                              !pipeline->vertexProcessor.backface;
                            break;
                        default:
                            break;
                        }
                    } else if (event.type == SDL_MOUSEMOTION) {
                        device.camera.Rotate((float)-event.motion.xrel,
                                             (float)event.motion.yrel);
                    }
                }

                if (controller) {
                    Sint16 rX = SDL_GameControllerGetAxis(
                      controller, SDL_CONTROLLER_AXIS_RIGHTX);
                    Sint16 rY = SDL_GameControllerGetAxis(
                      controller, SDL_CONTROLLER_AXIS_RIGHTY);
                    Sint16 lX = SDL_GameControllerGetAxis(
                      controller, SDL_CONTROLLER_AXIS_LEFTX);
                    Sint16 lY = SDL_GameControllerGetAxis(
                      controller, SDL_CONTROLLER_AXIS_LEFTY);

                    int deadZone = 3000;

                    if (rX > deadZone || rX < -deadZone || rY > deadZone ||
                        rY < -deadZone) {

                        device.camera.Rotate((float)(-rX * 0.00001),
                                             (float)(rY * 0.00001));
                    }
                    if (lY > deadZone || lY < -deadZone) {
                        device.camera.position +=
                          device.camera.front * (float)(lY * 0.000001);
                    }
                    if (lX > deadZone || lX < -deadZone) {
                        device.camera.position +=
                          glm::cross(device.camera.front, device.camera.up) *
                          (float)(lX * 0.000001);
                    }
                }

                // Tell device to render an object
                for (auto&& o : renderQueue)
                    pipeline->Render(o.second);

                fps_frames++;
                if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL * 1000) {
                    fps_lasttime = SDL_GetTicks();
                    fps_current  = fps_frames;
                    fps_frames   = 0;
                }

                renderText("FPS: " + std::to_string(fps_current), font,
                           &textSurface, foregroundColor, backgroundColor);

                SDL_BlitSurface(textSurface, NULL, windowSurface,
                                &textLocation);
                SDL_FreeSurface(textSurface);

                // Update the window with changes
                SDL_UpdateWindowSurface(window);
            }
            // TTF_CloseFont(font);
        } catch (const std::exception& ex) {
            printf(ex.what());
        }
    }
    SDL_FreeSurface(textSurface);
    close(&window);

    return 0;
}

bool init(SDL_Window** window, SDL_Surface** windowSurface, int screenWidth,
          int screenHeight) {

    // Attempt to init the video component of SDL and print an error if it fails
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        printf("SDL did not init! Error: %s\n", SDL_GetError());
        return false;
    } else {
        *window = SDL_CreateWindow(
          "SDL Test", 300, 300, screenWidth, screenHeight,
          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);

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

void renderText(std::string text, TTF_Font* font, SDL_Surface** surface,
                SDL_Color textColour, SDL_Color backgroundColour) {

    *surface =
      TTF_RenderText_Shaded(font, text.c_str(), textColour, backgroundColour);
}

void close(SDL_Window** window) {

    SDL_DestroyWindow(*window); // Destroy the window
    *window = NULL;
    IMG_Quit(); // Quit SDL image
    SDL_Quit(); // Quit out of SDL
}

// Register a controller so it can be used to control the camera
void RegisterController(int ContId, SDL_GameController** controller) {
    if (SDL_IsGameController(ContId)) {
        *controller = SDL_GameControllerOpen(ContId);
        if (controller) {
            std::cout << "Controller Registered" << std::endl;
        }
    }
}