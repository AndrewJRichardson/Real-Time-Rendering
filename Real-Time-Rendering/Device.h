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
        float*       zBuffer;
        int          zBufferSize;
        int          bufferWidth;
        int          bufferHeight;
        int          halfWidth;
        int          halfHeight;
        void         (Device::*currentRenderMode)(const Object& object, const glm::mat4& transformMatrix);
        bool         colourFlip;
        glm::mat4    viewMatrix;
        glm::mat4    perspectiveMatrix;
        int          screenSize;
        int          threadLimit;
        DebugTools   debugTool;

        //Consructors and Destructors
        REALTIME_API Device  (SDL_Surface& surface);
        REALTIME_API Device  (const Device&);
        REALTIME_API Device  (const Device&& device);
        REALTIME_API ~Device ();
        
        //Methods
        REALTIME_API void		Clear(const Camera& camera);
        REALTIME_API void		ChangePixel(int index, Uint32 colour);
        REALTIME_API void		DrawPoint(const glm::vec3& point, int r, int g, int b);
        REALTIME_API void		DrawLine(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API void		DrawLineBresenham(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API glm::vec3  Project(const glm::vec3& vert, const glm::mat4& transform);
        REALTIME_API glm::vec3  MapToScreen(glm::vec3& vert);
        // REALTIME_API void		Render(const Object& mesh);
        // REALTIME_API void		RenderPoints(const Object& object, const glm::mat4& transformMatrix);
        // REALTIME_API void		RenderWireframes(const Object& object, const glm::mat4& transformMatrix);
        REALTIME_API void		DrawScanLine(int currentY, const glm::vec3 pointA, const glm::vec3 pointB, const glm::vec3 pointC, const glm::vec3 pointD, int r, int g, int b);
        REALTIME_API float		InverseSlope(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API float		Slope(const glm::vec3& start, const glm::vec3& end);
        REALTIME_API float		Interpolate(float min, float max, float gradient);
        REALTIME_API float		Clamp(float value, float min = 0, float max = 1);
        // REALTIME_API void		DrawTriangle(glm::vec3& pointA, glm::vec3& pointB, glm::vec3& pointC);
        REALTIME_API void		DrawTriangle(glm::vec3&,glm::vec3&,glm::vec3&);
        // REALTIME_API void		RenderFill(const Object& object, const glm::mat4& transformMatrix);
        // REALTIME_API void		RenderTriangle(int count, int start, const Mesh& mesh, const glm::mat4& transformMatrix);
        REALTIME_API void		RenderTriangle(glm::vec3&, glm::vec3&, glm::vec3&);
    };
}

#endif // !DEVICE_H