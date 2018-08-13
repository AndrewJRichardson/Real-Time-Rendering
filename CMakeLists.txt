cmake_minimum_required(VERSION 3.10)


project(Real-Time-Rendering LANGUAGES CXX VERSION 0.0.1)

#Architecture variable is used when looking for libraries
#TODO: This should use a regex rather than target a specific version
#of Visual Studio
if (CMAKE_GENERATOR MATCHES "Visual Studio 15 2017 Win64")
    set(ARCHITECTURE "x64")
elseif(CMAKE_GENERATOR MATCHES "Visual Studio 15 2017")
    set(ARCHITECTURE "Win32")
endif()

message("Architecture is ${ARCHITECTURE}")

#Add paths to search for libraries
list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/Libs/SDL2-2.0.8/lib/${ARCHITECTURE};
                               ${CMAKE_SOURCE_DIR}/Libs/SDL2_ttf-2.0.14/lib/${ARCHITECTURE};
                               ${CMAKE_SOURCE_DIR}/Libs/SDL2_image-2.0.3/lib/${ARCHITECTURE})

#Prefix paths are used when using find path, it will prefix directories like lib and
#include with the given paths. If it wasn't for the architecture requirements could also be
#used for lib finding 
list(APPEND CMAKE_PREFIX_PATH  ${CMAKE_SOURCE_DIR}/Libs/SDL2-2.0.8;
                               ${CMAKE_SOURCE_DIR}/Libs/SDL2_ttf-2.0.14;
                               ${CMAKE_SOURCE_DIR}/Libs/glm/;
                               ${CMAKE_SOURCE_DIR}/Libs/SDL2_image-2.0.3)


#Stores the path to the file (minus the filename) inside the given var,
#there is probably a better way of doing this.
find_path(SDLin NAMES SDL.h)
find_path(sdlttfH NAMES SDL_ttf.h)
find_path(sdlimage NAMES SDL_image.h)
find_path(glm NAMES glm/vec3.hpp)

#Use the find path vars to populate include directories
#Also add the rendering library
include_directories(${glm})
include_directories(${SDLin})
include_directories(${sdlttfH})
include_directories(${sdlimage})
include_directories(${CMAKE_SOURCE_DIR}/Real-Time-Rendering)

#Use CMAKE_LIBRARY_PATH to find and store libraries
#Many of these libraries can be found with respective cmake
#modules, they don't account for custom locations though
find_library(SDL2 NAMES SDL2)
find_library(SDL2main NAMES SDL2main)
find_library(SDL2ttf NAMES SDL2_ttf)
find_library(SDL2image NAMES SDL2_image)

#If found prints the path, if not prints NOT FOUND
message("SDL: ${SDLin}")
message("SDLttf: ${sdlttfH}")
message("GLM: ${glm}")
message("SDL image: ${sdlimage}")

#Add subdirectories, cmake will process the CMakeLists file in each
#added directory
add_subdirectory(Real-Time-Rendering)
add_subdirectory(Real-Time-Rendering-Demos)

   