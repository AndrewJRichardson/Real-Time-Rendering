#ifndef DEVICE_H
#define DEVICE_H

#include "Exports.h"

#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <thread>
#include <vector>

#include "Camera.h"
#include "Mesh.h"
#include "Object.h"

namespace rtr {

/// Various utility functions for rendering objects
/**
 * Device is essentially an abstract representation of a GPU
 *
 * Responsible for drawing/clearing the frame buffer and the zBuffer
 */
class Device {
  public:
    // Members
    SDL_Surface& buffer;
    Camera&      camera;
    float*       zBuffer;
    int          zBufferSize;
    int          bufferWidth;
    int          bufferHeight;
    int          halfWidth;
    int          halfHeight;
    glm::mat4    viewMatrix;
    glm::mat4    projectionMatrix;
    int          screenSize;
    int          threadLimit; /// Thread limit for RenderThreaded method

    // Consructors and Destructors
    /// Default constructor
    /**
     * Surface is frame buffer that device will draw to and clear
     */
    REALTIME_API Device(SDL_Surface& surface, Camera& camera);
    REALTIME_API Device(const Device&);
    REALTIME_API Device(const Device&& device);
    REALTIME_API ~Device();
    // Methods
    /// Clears the frame and z-buffer
    /**
     * Also creates the view matrix, though this is planned to be moved
     */
    REALTIME_API void Clear();

    /// Draws a coloured pixel into the frame buffer
    REALTIME_API void DrawPixel(const glm::vec3&, int, int, int);

    /// Same as DrawPoint but uses Uints for r,g,b
    REALTIME_API void DrawPixel(const glm::vec3&, Uint8, Uint8, Uint8);

    /// Test feature, do not use
    REALTIME_API void DebugDraw(const glm::vec3&, int, int, int, SDL_Window&);

    /// DEPRECATED: Draws a line using the middle point recursion algorithm
    REALTIME_API void DrawLine(const glm::vec3&, const glm::vec3&);

    /// Draws a line using bresenhams line algorithm
    REALTIME_API void DrawLineBresenham(const glm::vec3&, const glm::vec3&);

    /// Projects a vertex into clip space
    /**
     * This method is just a multiplication now and will be removed
     * in future
     */
    REALTIME_API glm::vec3 Project(const glm::vec3&, const glm::mat4&);

    /// Turns clip space points into screen space points
    REALTIME_API glm::vec3 MapToScreen(glm::vec3&);

    /// Draws filled triangles using the scan line method
    REALTIME_API void DrawScanLine(int, int, int, const glm::vec3,
                                   const glm::vec3, const glm::vec3,
                                   const glm::vec3, const float, const float,
                                   int, int, int);

    /// Draws textured lines between two points using a scanline method
    /**
     * A and B are the left edge of a triangle C and D are the right edge
     *
     * gA, gB are the gradients for those lines, gZ is currently unused
     */
    REALTIME_API void DrawScanLineTexture(const int, int, int,
                                          const FaceVertSet&,
                                          const FaceVertSet&,
                                          const FaceVertSet&,
                                          const FaceVertSet&, const Object&,
                                          const float, const float);

    /// Calculates the inverse slope (how x in relation to y) for a line
    REALTIME_API float InverseSlope(const glm::vec3&, const glm::vec3&);

    /// Interpolates a point between two values based on the gradient
    REALTIME_API float Interpolate(float, float, float);

    /// Clamps a value between 0 and 1
    REALTIME_API float Clamp(float);

    /// Sorts triangles and and draws them using DrawScanLine
    REALTIME_API void RenderTriangle(glm::vec3&, glm::vec3&, glm::vec3&);

    /// Calculates the signed area of a triangle
    /**
     * Actually returns signed area x2 as for rendering purposes only the sign
     * is required
     */
    REALTIME_API float SignedArea(glm::vec3&, glm::vec3&, glm::vec3&);

    // REALTIME_API float      InterpolateX(glm::vec3&, glm::vec3&, glm::vec3&,
    // float, float, float); REALTIME_API float      InterpolateY(glm::vec3&,
    // glm::vec3&, glm::vec3&, float, float, float);
};
} // namespace rtr

#endif // !DEVICE_H