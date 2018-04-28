#include <iostream>
#include <thread>

#include "Device.h"


//Constructors
rtr::Device::Device(SDL_Surface& surface, Camera& camera) 
    : buffer(surface), camera(camera){
    bufferHeight      = buffer.h;
    bufferWidth       = buffer.w;
    halfWidth         = bufferWidth / 2;
    halfHeight        = bufferHeight / 2;
    screenSize        = bufferHeight * bufferWidth;
    zBuffer           = new float[screenSize];
    zBufferSize       = screenSize;
    debugTool         = {};
    perspectiveMatrix = glm::perspective(glm::radians(90.f), (float)bufferWidth / bufferHeight, 1.f, 100.0f);
    threadLimit       = 4;
}

//Move constructor
rtr::Device::Device(const Device&& device)  
    : buffer(device.buffer), camera(device.camera){
    bufferHeight      = device.bufferHeight;
    bufferWidth       = device.bufferWidth;
    halfWidth         = device.halfWidth;
    halfHeight        = device.halfHeight;
    screenSize        = device.screenSize;
    zBufferSize       = device.zBufferSize;
    perspectiveMatrix = device.perspectiveMatrix;
    debugTool         = device.debugTool;
}


//TODO: implement copy constructor, most copies are elided, but just in case
rtr::Device::Device(const Device& device) 
    : buffer(device.buffer), camera(device.camera) {
}



//Destructors
rtr::Device::~Device() {
}


//Methods
//! Remove once pointer code has been copied out for report
//TODO: Should be removable once pipeline is finished
//Creates a transform matrix and calls the currently set render mode
// void rtr::Device::Render(const Object& object) {
// 	glm::mat4 modelMatrix      = glm::translate(glm::mat4(), object.mesh.position);
// 	glm::mat4 transformMatrix  = perspectiveMatrix * viewMatrix * modelMatrix;
// 	(this->*currentRenderMode) (object, transformMatrix);
// }


//TODO: recreating the view matrix should be seperate
//Clears the buffer and recreates the viewMatrix
void rtr::Device::Clear() {
    std::fill    (zBuffer, zBuffer + zBufferSize, 3000);
    SDL_FillRect (&buffer, NULL, SDL_MapRGB(buffer.format, 0x00, 0x00, 0x00));
    viewMatrix = camera.LookAt();
}



//Draws a pixel onto the device buffer
void rtr::Device::DrawPoint(const glm::vec3& point, int r, int g, int b) {
    
    if (point.x >= 0 && point.y >= 0 && point.x < bufferWidth && point.y < bufferHeight-1) {
        int index = ((int)point.x + ((int)point.y * bufferWidth));
        if (zBuffer[index] < (int)point.z) {
            return;
        }

         zBuffer[index] = point.z;
        *((Uint32*)buffer.pixels + index) = SDL_MapRGB(buffer.format, (Uint8)r, (Uint8)g, (Uint8)b);
    }
}

void rtr::Device::DrawPoint(const glm::vec3& point, Uint8 r, Uint8 g, Uint8 b) {
    
    if (point.x >= 0 && point.y >= 0 && point.x < bufferWidth && point.y < bufferHeight-1) {
        int index = ((int)point.x + ((int)point.y * bufferWidth));
        if (zBuffer[index] < point.z) {
            return;
        }
        zBuffer[index] = point.z;

        *((Uint32*)buffer.pixels + index) = SDL_MapRGB(buffer.format, r, g, b);
    }
}


void rtr::Device::DebugDraw(const glm::vec3& point, int r, int g, int b, SDL_Window& window) {
    DrawPoint(point, r, g, b);
    SDL_UpdateWindowSurface(&window);
}

//Projects a vertices into clip space
glm::vec3 rtr::Device::Project(const glm::vec3& vert, const glm::mat4& transform) {
	glm::vec4 t{ vert, 1 };
    return transform * t;
}

//Takes clip space coords and maps them to screen space
glm::vec3 rtr::Device::MapToScreen(glm::vec3& vert){
    vert.x = (vert.x * bufferWidth  + halfWidth);
    vert.y = (vert.y * bufferHeight + halfHeight);
    return vert;
}


//Draws filled triangles using the scan line method
//TODO: Can be optimised in the same manner that scan line texture has been
void rtr::Device::DrawScanLine(const int currentY, const glm::vec3 pointA, 
                               const glm::vec3 pointB, const glm::vec3 pointC, 
                               const glm::vec3 pointD, int r, int g, int b) {

    float gradientA = pointA.y != pointB.y ? (currentY - pointA.y) / (pointB.y - pointA.y) : 1;
    float gradientB = pointC.y != pointD.y ? (currentY - pointC.y) / (pointD.y - pointC.y) : 1;

    int sx = (int)Interpolate(pointA.x, pointB.x, gradientA);
    int ex = (int)Interpolate(pointC.x, pointD.x, gradientB);

    float z1 = Interpolate(pointA.z, pointB.z, gradientA);
    float z2 = Interpolate(pointC.z, pointD.z, gradientB);

    for (int x = sx; x < ex; x++) {

        float gradient = (x - sx) / (float)(ex - sx);
        float z = Interpolate(z1, z2, gradient);
        DrawPoint(glm::vec3(x, currentY, z), r, g, b);
    }
}


void rtr::Device::DrawScanLineTexture(const int currentY, const FaceVertSet& a,
                                      const FaceVertSet& b, const FaceVertSet& c,
                                      const FaceVertSet& d, const Object& object,
                                      const float gA, const float gB, const float gZ){

    int sx = (int)Interpolate(a.v.x, b.v.x, gA);
    int ex = (int)Interpolate(c.v.x, d.v.x, gB);

    float z1 = Interpolate(a.v.z, b.v.z, gA);
    float z2 = Interpolate(c.v.z, d.v.z, gB);


    SDL_Surface* texture = object.texture;

    float su = Interpolate(a.vt.x, b.vt.x, gA);
    float eu = Interpolate(c.vt.x, d.vt.x, gB);
    float sv = Interpolate(a.vt.y, b.vt.y, gA);
    float ev = Interpolate(c.vt.y, d.vt.y, gB);

    Uint8 r, g, bl;

    float gradInc = 1 / (float)(ex - sx);
    float gradient = 0;

    for (int x = sx; x < ex; x++) {
        float z = Interpolate(z1, z2, gradient);
        float u = Interpolate(su, eu, gradient);
        float v = Interpolate(sv, ev, gradient);
        gradient += gradInc;
        u *= texture->w;
        v *= texture->h;
        int index = ((int)u + (int)v * texture->w);
        SDL_GetRGB(*((Uint32*)texture->pixels + index), texture->format, &r, &g, &bl);
        DrawPoint(glm::vec3(x, currentY, z), r, g, bl);
    }
}

// //No longer used, remains for testing purposes only
// void rtr::Device::DrawScanLineTextureOld(const int currentY, const FaceVertSet& a,
//                                       const FaceVertSet& b, const FaceVertSet& c,
//                                       const FaceVertSet& d, const Object& object)
                                      
//     float gradientA = a.v.y != b.v.y ? (currentY - a.v.y) / (b.v.y - a.v.y) : 1;
//     float gradientB = c.v.y != d.v.y ? (currentY - c.v.y) / (d.v.y - c.v.y) : 1;

//     int sx = (int)Interpolate(a.v.x, b.v.x, gradientA);
//     int ex = (int)Interpolate(c.v.x, d.v.x, gradientB);

//     float z1 = Interpolate(a.v.z, b.v.z, gradientA);
//     float z2 = Interpolate(c.v.z, d.v.z, gradientB);

//     SDL_Surface* texture = object.texture;

//     float su = Interpolate(a.vt.x, b.vt.x, gradientA);
//     float eu = Interpolate(c.vt.x, d.vt.x, gradientB);
//     float sv = Interpolate(a.vt.y, b.vt.y, gradientA);
//     float ev = Interpolate(c.vt.y, d.vt.y, gradientB);
 
//     Uint8 r, g, bl;

//     for (int x = sx; x < ex; x++) {
//         float gradient = (x - sx) / (float)(ex - sx);
//         float z = Interpolate(z1, z2, gradient);
//         float u = Interpolate(su, eu, gradient);
//         float v = Interpolate(sv, ev, gradient);
//         u *= texture->w;
//         v *= texture->h;
//         int index = ((int)u + (int)v * texture->w);
//         SDL_GetRGB(*((Uint32*)texture->pixels + index), texture->format, &r, &g, &bl);
//         DrawPoint(glm::vec3(x, currentY, z), r, g, bl);
//     }
// }


void rtr::Device::RenderTriangle(glm::vec3& point1, glm::vec3& point2,
                                 glm::vec3& point3) {
    if (point1.z > 0 && point2.z > 0 && point3.z > 0) {
        DrawTriangle(point1, point2, point3);
    }
}

//Draws lines using the middle point method
//Legacy: Use bresenham function where possible
void rtr::Device::DrawLine(const glm::vec3& start, const glm::vec3& end) {
    glm::vec3 distance = end - start;

    if (glm::length(distance) < 2) {
        return;
    }

    glm::vec3 middle = start + distance / 2.f;

    DrawPoint(middle, 0xff, 0xff, 0xff);
    DrawLine(start, middle);
    DrawLine(end, middle);
}


//TODO: remove once pipeline is finished
//Draws filled triangles using the draw scanline method
void rtr::Device::DrawTriangle(glm::vec3& pointA, glm::vec3& pointB, glm::vec3& pointC) {

    int r = 0xFF, g = 0xFF, b = 0xFF;
    if (pointA.y > pointB.y) {
        glm::vec3 tPoint = pointB;
        pointB = pointA;
        pointA = tPoint;
    }

    if (pointB.y > pointC.y) {
        glm::vec3 tPoint = pointC;
        pointC = pointB;
        pointB = tPoint;
    }

    if (pointA.y > pointB.y) {
        glm::vec3 tPoint = pointB;
        pointB = pointA;
        pointA = tPoint;
    }

    float invAB, invAC;

    if (pointB.y - pointA.y > 0) {
        invAB = InverseSlope(pointA, pointB);
    } else {
        invAB = 0;
    }

    if (pointC.y - pointA.y > 0) {
        invAC = InverseSlope(pointA, pointC);
    } else {
        invAC = 0;
    }

    bool right = false, left = false;

    if (pointB.y - pointA.y > 0) {
        invAB = InverseSlope(pointA, pointB);
    }
    else if (pointB.x > pointA.x) {
        right = true;
    }
    else {
        left = true;
    }

    if (right || (!left && invAB > invAC)) {
        for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {
            if (y < pointB.y) {
                DrawScanLine(y, pointA, pointC, pointA, pointB, r, g, b);
            }
            else {
                DrawScanLine(y, pointA, pointC, pointB, pointC, r, g, b);
            }
        }
    }
    else {
        for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {
            if (y < pointB.y) {
                DrawScanLine(y, pointA, pointB, pointA, pointC, r, g, b);
            }
            else {
                DrawScanLine(y, pointB, pointC, pointA, pointC, r, g, b);
            }
        }
    }

}


//TODO: move into RasterizeWireframe 
void rtr::Device::DrawLineBresenham(const glm::vec3& start, const glm::vec3& end) {

    int x  = (int)start.x; //Store both values of both vectors
    int y  = (int)start.y; //so we don't have to cast them repeatedly in the following loop 
    int ex = (int)end.x;
    int ey = (int)end.y;

    int dx = std::abs((int)end.x - (int)start.x);
    int dy = std::abs((int)end.y - (int)start.y);

    int error = dx - dy; //error is used to determine which pixel we draw too

    int ix; //used to store the values we will increment/decrement the error by
    int iy; //increment and decrement is based on which direction the line is going

    if (x < end.x) {
        ix = 1;
    }
    else {
        ix = -1;
    }

    if (y < end.y) {
        iy = 1;
    }
    else {
        iy = -1;
    }


    bool complete = false;

    while (!complete) {
        DrawPoint(glm::vec3(x, y, start.z), 0xff, 0xff, 0xff); //Draw the current point

        if (x == ex && y == ey) { //Exit if the vectors match
            complete = true;
            continue;
        }

        //A difference of 0.5 is used in bresenham's algorithm to determine whether we should move the passive axis along
        //since we are using integers we need to scale the error by 2 to account for the loss of precision
        int tError = error * 2;
        if (tError > -dy) {
            error -= dy;
            x += ix;
        }
        if (tError < dx) {
            error += dx;
            y += iy;
        }
    }
}


//Calculates an inverse slope, x as it relates to y
float rtr::Device::InverseSlope(const glm::vec3& start, const glm::vec3& end) {
        return (end.x - start.x) / (end.y - start.y);
    }


//Clamps a value between 0 and 1
float rtr::Device::Clamp(float value) {
    if(value < 0)
        return 0;
    else if(value > 1)
        return 1;
    else
        return value;
}

//Interpolates between the values based on the gradient
float rtr::Device::Interpolate(float min, float max, float gradient) {
    return min + (max - min) * Clamp(gradient);
}


//Returns the 2x the area of a triangle
float rtr::Device::SignedArea(glm::vec3& vert1, glm::vec3& vert2, glm::vec3& vert3){
    glm::vec3 a = vert2 - vert1;
    glm::vec3 b = vert3 - vert1; 

    //Technically this result should be divided by 2 to get the actual area
    //however, we are only interested in whether the result is pos or neg
    //so the divide is a redundant operation
    return ((a.x*b.y)-(a.y*b.x));
}


//Part of an optimisation of the fill/texture renderers that was never finished
// float rtr::Device::InterpolateX(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,
//                                 float i1, float i2, float i3){
//      //To calculate the value of the interpolant, a 4th point is created and is given the y of p1, 
//     //so that the y remains constant, giving the value of i as it relates to x
//     //to calculate the x for p4 some algebra needs to be applied, since y4 = y1 then:
//     // (p2.x - p3.x)     (p4.x - p3.x)     (p4.x - p3.x)       (p2.x - p3.x)
//     // -------------  =  -------------  =  -------------  so:  ------------- * (p1.y - p3.y) = p4.x - p3.x
//     // (p2.y - p3.y)     (p4.y - p3.y)     (p1.y - p3.y)       (p2.y - p3.y)

//     if (p2.y - p3.y == 0)
//         return 0;
//     float inter = ((i2 - i3)/(p2.y - p3.y)) * (p1.y - p3.y) + i3;
//     return inter - i1;
// }

// //Part of an optimisation of the fill/texture renderers that was never finished
// float rtr::Device::InterpolateY(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,
//                                 float i1, float i2, float i3){
//     //Similar idea to Interpolate X
//     float inter = ((i2 - i3)/(p2.x - p3.x)) * (p1.x - p3.x) + i3;
//     return inter - i1; 
}