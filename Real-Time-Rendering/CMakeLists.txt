cmake_minimum_required(VERSION 3.10)

project(Real-Time-Rendering-Lib LANGUAGES CXX VERSION 0.0.1)
set(headers     Device.h;
                Camera.h;
                Object.h;
                Mesh.h;
                Pipeline.h;
                ViewPerspective.h;
                ViewOrthogonal.h;
                RasterizeVertex.h;
                RasterizeWireframe.h;
                RasterizeTextured.h;
                RasterizeFilled.h;
                VertexProcessor.h;
                VertexShader.h;
                ObjectParser.h;
                DebugTools.h;
                Exports.h)

set(sourceFiles Device.cpp;
                Camera.cpp;
                Object.cpp;
                Pipeline.cpp;
                ViewPerspective.cpp;
                ViewOrthogonal.cpp;
                RasterizeVertex.cpp;
                RasterizeWireframe.cpp;
                RasterizeTextured.cpp;
                RasterizeFilled.cpp;
                VertexProcessor.cpp;
                VertexShader.cpp;
                Mesh.cpp;
                ObjectParser.cpp;
                DebugTools.cpp)

add_library(Real-Time-Rendering-Lib ${sourceFiles} ${headers})
target_link_libraries(Real-Time-Rendering-Lib ${SDL2} ${SDL2main} ${SDL2image})

if(BUILD_SHARED_LIBS)
    target_compile_definitions(Real-Time-Rendering-Lib PRIVATE REALTIME_EXPORTS)
endif()