#Cmake lists file for the rendering library demo


cmake_minimum_required(VERSION 3.10)

#Demo and lib are treated as seperate projects
project(Real-Time-Rendering-Demo LANGUAGES CXX VERSION 0.0.1)

#Add the demo target and the sourcefiles it needs to create Demo.exe
add_executable(Demo BasicCube.cpp) 

#link Demo target to the reqired libraries
target_link_libraries(Demo ${SDL2} ${SDL2ttf} Real-Time-Rendering-Lib)

#Copy the resources directory which contains object files and fonts
set (source "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/resources")
add_custom_command(
 TARGET Demo POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination} 
 COMMENT "Resources has been copied"
)

#Copy all the needed DLLs to the build directory
#TODO: Find a cleaner way to do this
add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/Libs/SDL2-2.0.8/lib/${ARCHITECTURE}/SDL2.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/SDL2.dll")

add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/Libs/SDL2_ttf-2.0.14/lib/${ARCHITECTURE}/SDL2_ttf.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/SDL2_ttf.dll")

add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/Libs/SDL2_image-2.0.3/lib/${ARCHITECTURE}/zlib1.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/zlib1.dll")

add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/Libs/SDL2_ttf-2.0.14/lib/${ARCHITECTURE}/libfreetype-6.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/libfreetype-6.dll")

add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_SOURCE_DIR}/Libs/SDL2_image-2.0.3/lib/${ARCHITECTURE}/SDL2_image.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/SDL2_image.dll")


add_custom_command(TARGET Demo POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${CMAKE_BINARY_DIR}/Real-Time-Rendering/$<CONFIG>/Real-Time-Rendering-Lib.dll"
                   "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/Real-Time-Rendering-Lib.dll")