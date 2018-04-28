#ifndef DEVICE_H
#define DEVICE_H

#include "Exports.h"

#include <math.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <thread>
#include <algorithm>

#include "Camera.h"
#include "Mesh.h"
#include "Object.h"

#include "DebugTools.h"

namespace rtr {

    class Device {
    public:
        //Members
        SDL_Surface& buffer;
        Camera&      camera;
        float*       zBuffer;
        int          zBufferSize;
        int          bufferWidth;
        int          bufferHeight;
        int          halfWidth;
        int          halfHeight;
        // void         (Device::*currentRenderMode)(const Object& object, const glm::mat4& transformMatrix);
        // bool         colourFlip;
        glm::mat4    viewMatrix;
        glm::mat4    perspectiveMatrix;
        int          screenSize;
        int          threadLimit;
        DebugTools   debugTool;

        //Consructors and Destructors
        REALTIME_API Device  (SDL_Surface& surface, Camera& camera);
        REALTIME_API Device  (const Device&);
        REALTIME_API Device  (const Device&& device);
        REALTIME_API ~Device ();
        
        //Methods
        REALTIME_API void		Clear();
        REALTIME_API void		ChangePixel(int index, Uint32 colour);
        REALTIME_API void		DrawPoint(const glm::vec3& point, int r, int g, int b);
        REALTIME_API void		DrawPoint(const glm::vec3& point, Uint8 r, Uint8 g, Uint8 b);
        REALTIME_API void       DebugDraw(const glm::vec3& point, int r, int g, int b, SDL_Window& window);
        REALTIME_API void		DrawLine(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API void		DrawLineBresenham(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API glm::vec3  Project(const glm::vec3& vert, const glm::mat4& transform);
        REALTIME_API glm::vec3  MapToScreen(glm::vec3& vert);
        REALTIME_API void		DrawScanLine(int currentY, const glm::vec3 pointA, 
                                    const glm::vec3 pointB, const glm::vec3 pointC, 
                                    const glm::vec3 pointD, int r, int g, int b);
        REALTIME_API void       DrawScanLine(int, int, int, float, float, float, int, int, int);
        REALTIME_API void       DrawScanLine(int y, int startX, int endX, 
                                    float startZ, float endZ, int r, int g, int b);
        REALTIME_API float		InverseSlope(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API float		Slope(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API float		Interpolate(float min, float max, float gradient);
        REALTIME_API float		Clamp(float value);
        REALTIME_API void		DrawTriangle(glm::vec3&,glm::vec3&,glm::vec3&);
        REALTIME_API void		RenderTriangle(glm::vec3&, glm::vec3&, glm::vec3&);
        REALTIME_API void       DrawScanLineTexture(const int currentY, const FaceVertSet&,
                                    const FaceVertSet&, const FaceVertSet&,
                                    const FaceVertSet&, const Object&,
                                    const float, const float, const float);
        REALTIME_API float      SignedArea(glm::vec3&, glm::vec3&, glm::vec3&);
        // REALTIME_API float      InterpolateX(glm::vec3&, glm::vec3&, glm::vec3&, float, float, float);
        // REALTIME_API float      InterpolateY(glm::vec3&, glm::vec3&, glm::vec3&, float, float, float);
        //Used for testing only
        // REALTIME_API float      DrawScanLineTextureOld(const int currentY, const FaceVertSet& a,
        //                             const FaceVertSet& b, const FaceVertSet& c,
        //                             const FaceVertSet& d, const Object& object);

    };
}

#endif // !DEVICE_H