#include <iostream>
#include <thread>

#include "Device.h"

// Constructors
rtr::Device::Device(SDL_Surface& surface, Camera& camera)
    : buffer(surface), camera(camera) {

    bufferHeight     = buffer.h;
    bufferWidth      = buffer.w;
    halfWidth        = bufferWidth / 2;
    halfHeight       = bufferHeight / 2;
    screenSize       = bufferHeight * bufferWidth;
    zBuffer          = new float[screenSize];
    zBufferSize      = screenSize;
    threadLimit      = 4;
    projectionMatrix = glm::perspective(
      glm::radians(90.f), (float)bufferWidth / bufferHeight, 1.f, 100.0f);
}

// Move constructor
rtr::Device::Device(const Device&& device)
    : buffer(device.buffer), camera(device.camera) {
    bufferHeight     = device.bufferHeight;
    bufferWidth      = device.bufferWidth;
    halfWidth        = device.halfWidth;
    halfHeight       = device.halfHeight;
    screenSize       = device.screenSize;
    zBufferSize      = device.zBufferSize;
    projectionMatrix = device.projectionMatrix;
}

// TODO: implement copy constructor, most copies are elided, but just in case
rtr::Device::Device(const Device& device)
    : buffer(device.buffer), camera(device.camera) {}

// Destructors
rtr::Device::~Device() {}

// Methods
//! Remove once pointer code has been copied out for report

// TODO: recreating the view matrix should be seperate
// Clears the buffer and recreates the viewMatrix
void rtr::Device::Clear() {
    std::fill(zBuffer, zBuffer + zBufferSize, 3000);
    SDL_FillRect(&buffer, NULL, SDL_MapRGB(buffer.format, 0x00, 0x00, 0x00));
    viewMatrix = camera.LookAt();
}

// Draws a pixel onto the device buffer
void rtr::Device::DrawPixel(const glm::vec3& point, int r, int g, int b) {

    if (point.x >= 0 && point.y >= 0 && point.x < bufferWidth &&
        point.y < bufferHeight - 1) {

        int index = ((int)point.x + ((int)point.y * bufferWidth));
        if (zBuffer[index] < (int)point.z) {
            return;
        }

        zBuffer[index] = point.z;
        *((Uint32*)buffer.pixels + index) =
          SDL_MapRGB(buffer.format, (Uint8)r, (Uint8)g, (Uint8)b);
    }
}

void rtr::Device::DrawPixel(const glm::vec3& point, Uint8 r, Uint8 g, Uint8 b) {

    if (point.x >= 0 && point.y >= 0 && point.x < bufferWidth &&
        point.y < bufferHeight - 1) {

        int index = ((int)point.x + ((int)point.y * bufferWidth));
        if (zBuffer[index] < point.z) {
            return;
        }
        zBuffer[index] = point.z;

        *((Uint32*)buffer.pixels + index) = SDL_MapRGB(buffer.format, r, g, b);
    }
}

// Testing purporses only
void rtr::Device::DebugDraw(const glm::vec3& point, int r, int g, int b,
                            SDL_Window& window) {
    DrawPixel(point, r, g, b);
    SDL_UpdateWindowSurface(&window);
}

glm::vec3 rtr::Device::Project(const glm::vec3& vert,
                               const glm::mat4& transform) {
    glm::vec4 t{vert, 1};
    return transform * t;
}

glm::vec3 rtr::Device::MapToScreen(glm::vec3& vert) {
    vert.x = (vert.x * bufferWidth + halfWidth);
    vert.y = (vert.y * bufferHeight + halfHeight);
    return vert;
}

void rtr::Device::DrawScanLine(const int currentY, int leftX, int rightX,
                               const glm::vec3 leftStart,
                               const glm::vec3 leftEnd,
                               const glm::vec3 rightStart,
                               const glm::vec3 rightEnd, const float gA,
                               const float gB, int r, int g, int b) {

    float z1 = Interpolate(leftStart.z, leftEnd.z, gA);
    float z2 = Interpolate(rightStart.z, rightEnd.z, gA);

    float gradInc  = 1 / (float)(rightX - leftX);
    float gradient = 0;

    for (int x = leftX; x < rightX; x++) {

        float z = Interpolate(z1, z2, gradient);
        gradient += gradInc;
        DrawPixel(glm::vec3(x, currentY, z), r, g, b);
    }
}

void rtr::Device::DrawScanLineTexture(
  const int currentY, int leftX, int rightX, const FaceVertSet& a,
  const FaceVertSet& b, const FaceVertSet& c, const FaceVertSet& d,
  const Object& object, const float gA, const float gB) {

    float z1 = Interpolate(a.v.z, b.v.z, gA);
    float z2 = Interpolate(c.v.z, d.v.z, gB);

    float su = Interpolate(a.vt.x, b.vt.x, gA);
    float eu = Interpolate(c.vt.x, d.vt.x, gB);
    float sv = Interpolate(a.vt.y, b.vt.y, gA);
    float ev = Interpolate(c.vt.y, d.vt.y, gB);

    Uint8 r, g, bl;

    float gradInc  = 1 / (float)(rightX - leftX);
    float gradient = 0;
    int   index;

    for (int x = leftX; x < rightX; x++) {
        float z = Interpolate(z1, z2, gradient);
        float u = Interpolate(su, eu, gradient);
        float v = Interpolate(sv, ev, gradient);

        gradient += gradInc;

        u *= object.texture->w;
        v *= object.texture->h;
        index = ((int)u + (int)v * object.texture->w);

        SDL_GetRGB(*((Uint32*)object.texture->pixels + index),
                   object.texture->format, &r, &g, &bl);

        DrawPixel(glm::vec3(x, currentY, z), r, g, bl);
    }
}

// Draws lines using the middle point method
// Legacy: Use bresenham function where possible
void rtr::Device::DrawLine(const glm::vec3& start, const glm::vec3& end) {
    glm::vec3 distance = end - start;

    if (glm::length(distance) < 2) {
        return;
    }

    glm::vec3 middle = start + distance / 2.f;

    DrawPixel(middle, 0xff, 0xff, 0xff);
    DrawLine(start, middle);
    DrawLine(end, middle);
}

void rtr::Device::RenderTriangle(glm::vec3& pointA, glm::vec3& pointB,
                                 glm::vec3& pointC) {
    int r = 0xff, g = 0xff, b = 0xff;

    if (pointA.y > pointB.y) {
        glm::vec3 tPoint = pointB;
        pointB           = pointA;
        pointA           = tPoint;
    }

    if (pointB.y > pointC.y) {
        glm::vec3 tPoint = pointC;
        pointC           = pointB;
        pointB           = tPoint;
    }

    if (pointA.y > pointB.y) {
        glm::vec3 tPoint = pointB;
        pointB           = pointA;
        pointA           = tPoint;
    }

    float invAB = 0, invAC = 0, invBC = 0;

    if (pointB.y - pointA.y > 0)
        invAB = InverseSlope(pointA, pointB);

    if (pointC.y - pointA.y > 0)
        invAC = InverseSlope(pointA, pointC);

    if (pointC.y - pointB.y > 0)
        invBC = InverseSlope(pointB, pointC);

    float gAB, gBC, gAC, gradAB = 0, gradBC = 0, gradAC = 0;

    if (pointA.y != pointB.y)
        gAB = 1 / (pointB.y - pointA.y);
    else
        gAB = 1;

    if (pointA.y != pointC.y)
        gAC = 1 / (pointC.y - pointA.y);
    else
        gAC = 1;

    if (pointB.y != pointC.y)
        gBC = 1 / (pointC.y - pointB.y);
    else
        gBC = 1;

    float ABx = pointA.x;
    float ACx = pointA.x;
    float BCx = pointB.x;

    bool leftB = false;
    if (SignedArea(pointA, pointB, pointC) < 0)
        leftB = true;

    for (int i = (int)pointA.y; i < (int)pointC.y; i++) {
        if (i < pointB.y - 1) {
            if (leftB)
                DrawScanLine(i, (int)ABx, (int)ACx, pointA, pointB, pointA,
                             pointC, gradAB, gradAC, r, g, b);
            else
                DrawScanLine(i, (int)ACx, (int)ABx, pointA, pointC, pointA,
                             pointB, gradAC, gradAB, r, g, b);
            gradAB += gAB;
            ABx += invAB;
        } else {
            if (leftB)
                DrawScanLine(i, (int)BCx, (int)ACx, pointB, pointC, pointA,
                             pointC, gradBC, gradAC, r, g, b);
            else
                DrawScanLine(i, (int)ACx, (int)BCx, pointA, pointC, pointB,
                             pointC, gradAC, gradBC, r, g, b);
            gradBC += gBC;
            BCx += invBC;
        }
        gradAC += gAC;
        ACx += invAC;
    }
}

void rtr::Device::DrawLineBresenham(const glm::vec3& start,
                                    const glm::vec3& end) {
    // Store both values of both vectors so we don't have to cast them
    // repeatedly in the loop
    int startX = (int)start.x;
    int startY = (int)start.y;
    int endX   = (int)end.x;
    int endY   = (int)end.y;

    int distX = std::abs((int)end.x - (int)start.x);
    int distY = std::abs((int)end.y - (int)start.y);
    int error = distX - distY;
    int incX  = -1;
    int incY  = -1;

    // Which way is the line going to be drawn
    if (startX < end.x) {
        incX = 1;
    }
    if (startY < end.y) {
        incY = 1;
    }

    bool complete = false;

    while (!complete) {
        DrawPixel(glm::vec3(startX, startY, start.z), 0xff, 0xff, 0xff);

        if (startX == endX && startY == endY) {
            complete = true;
            continue;
        }

        // Mult by 2 to account for precision loss of using int
        // instead of floats
        int tError = error * 2;
        if (tError > -distY) {
            error -= distY;
            startX += incX;
        }
        if (tError < distX) {
            error += distX;
            startY += incY;
        }
    }
}

// Calculates an inverse slope, x as it relates to y
float rtr::Device::InverseSlope(const glm::vec3& start, const glm::vec3& end) {
    return (end.x - start.x) / (end.y - start.y);
}

// Clamps a value between 0 and 1
float rtr::Device::Clamp(float value) {
    if (value < 0)
        return 0;
    else if (value > 1)
        return 1;
    else
        return value;
}

// Interpolates between the values based on the gradient
float rtr::Device::Interpolate(float min, float max, float gradient) {
    return min + (max - min) * Clamp(gradient);
}

// Returns the 2x the area of a triangle
float rtr::Device::SignedArea(glm::vec3& vert1, glm::vec3& vert2,
                              glm::vec3& vert3) {

    glm::vec3 a = vert2 - vert1;
    glm::vec3 b = vert3 - vert1;

    // Technically this result should be divided by 2 to get the actual area
    // however, we are only interested in whether the result is pos or neg
    // so the divide is a redundant operation
    return ((a.x * b.y) - (a.y * b.x));
}

// Part of an optimisation of the fill/texture renderers that was never finished
// float rtr::Device::InterpolateX(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,
//                                 float i1, float i2, float i3){
//      //To calculate the value of the interpolant, a 4th point is created and
//      is given the y of p1,
//     //so that the y remains constant, giving the value of i as it relates to
//     x
//     //to calculate the x for p4 some algebra needs to be applied, since y4 =
//     y1 then:
//     // (p2.x - p3.x)     (p4.x - p3.x)     (p4.x - p3.x)       (p2.x - p3.x)
//     // -------------  =  -------------  =  -------------  so:  -------------
//     * (p1.y - p3.y) = p4.x - p3.x
//     // (p2.y - p3.y)     (p4.y - p3.y)     (p1.y - p3.y)       (p2.y - p3.y)

//     if (p2.y - p3.y == 0)
//         return 0;
//     float inter = ((i2 - i3)/(p2.y - p3.y)) * (p1.y - p3.y) + i3;
//     return inter - i1;
// }

// //Part of an optimisation of the fill/texture renderers that was never
// finished float rtr::Device::InterpolateY(glm::vec3& p1, glm::vec3& p2,
// glm::vec3& p3,
//                                 float i1, float i2, float i3){
//     //Similar idea to Interpolate X
//     float inter = ((i2 - i3)/(p2.x - p3.x)) * (p1.x - p3.x) + i3;
//     return inter - i1;
// }