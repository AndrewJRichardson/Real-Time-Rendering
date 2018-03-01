#include <iostream>
#include <thread>

#include "Device.h"



//Constructors
rtr::Device::Device(SDL_Surface& surface) : buffer(surface) {
    colourFlip        = true;
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
rtr::Device::Device(const Device&& device): buffer(device.buffer) {
    colourFlip        = device.colourFlip;
    bufferHeight      = device.bufferHeight;
    bufferWidth       = device.bufferWidth;
    halfWidth         = device.halfWidth;
    halfHeight        = device.halfHeight;
    screenSize        = device.screenSize;
    zBufferSize       = device.zBufferSize;
    perspectiveMatrix = device.perspectiveMatrix;
    debugTool         = device.debugTool;
}


//TODO implement copy constructor, most copies are elided but just in case
rtr::Device::Device(const Device& device) : buffer(device.buffer) {
    std::cout << "copy called" << std::endl;
}



//Destructors
rtr::Device::~Device() {
    //delete[] zBuffer;
}


//Methods
//TODO: Should be removable once pipeline is finished
//Creates a transform matrix and calls the currently set render mode
// void rtr::Device::Render(const Object& object) {
// 	glm::mat4 modelMatrix      = glm::translate(glm::mat4(), object.mesh.position);
// 	glm::mat4 transformMatrix  = perspectiveMatrix * viewMatrix * modelMatrix;
// 	(this->*currentRenderMode) (object, transformMatrix);
// }


//Clears the buffer and recreates the viewMatrix
void rtr::Device::Clear(const Camera& camera) {
    std::fill    (zBuffer, zBuffer + zBufferSize, 3000);
    SDL_FillRect (&buffer, NULL, SDL_MapRGB(buffer.format, 0x00, 0x00, 0x00));

    //colourFlip = false;
    viewMatrix = camera.LookAt();
}



//Draws a pixel onto the device buffer
void rtr::Device::DrawPoint(const glm::vec3& point, int r, int g, int b) {
    
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
    return transform * glm::vec4(vert, 1);
}

//Takes clip space coords and maps them to screen space
glm::vec3 rtr::Device::MapToScreen(glm::vec3& vert){
    vert.x = (vert.x * bufferWidth  + halfWidth);
    vert.y = (vert.y * bufferHeight + halfHeight);
    return vert;
}


//TODO: remove once pipeline is finished
//Draws filled triangles using the scan line method
void rtr::Device::DrawScanLine(const int currentY, const glm::vec3 pointA, const glm::vec3 pointB, const glm::vec3 pointC, const glm::vec3 pointD, int r, int g, int b) {
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

void rtr::Device::DrawScanLine(int y, int startX, int endX, float z, float zInc, float zY, int r, int g, int b) {
    // float gradientA = pointA.y != pointB.y ? (currentY - pointA.y) / (pointB.y - pointA.y) : 1;
    // float gradientB = pointC.y != pointD.y ? (currentY - pointC.y) / (pointD.y - pointC.y) : 1;

    // int sx = (int)Interpolate(pointA.x, pointB.x, gradientA);
    // int ex = (int)Interpolate(pointC.x, pointD.x, gradientB);

    // float z1 = Interpolate(pointA.z, pointB.z, gradientA);
    // float z2 = Interpolate(pointC.z, pointD.z, gradientB);
    //DrawPoint(glm::vec3(startX, y, zY), r, g, b);
    for (int x = startX + 1; x < endX; x++) {
        // float gradient = (x - startX) / (float)(endX - startX);
        // float z = Interpolate(z1, z2, gradient);
        z += zInc;
        DrawPoint(glm::vec3(x, y, z), r, g, b);
    }
}



void rtr::Device::RenderTriangle(glm::vec3& point1, glm::vec3& point2,
                                 glm::vec3& point3) {
    if (point1.z > 0 && point2.z > 0 && point3.z > 0) {
        DrawTriangle(point1, point2, point3);
    }
}


//TODO: remove once pipeline is finished
//Draws lines using the middle point method
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
/*	if (colourFlip) {
        r = 0xff;
        g = 0xff;
        b = 0xff;
    }
    else {
        r = 0xff;
        g = 0x00;
        b = 0x00;
    }*/

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

    colourFlip = !colourFlip;
}

//TODO: remove once pipeline is finished
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

//TODO: These math functions may need removing once pipeline is finished, 
//or possibly moving to a more relevant class if they are used by more than 
//one rendering method
//remove unused math functions
float rtr::Device::Slope(const glm::vec3& start, const glm::vec3& end) {
    return (end.y - start.y) / (end.y - start.y);
    
}


float rtr::Device::InverseSlope(const glm::vec3& start, const glm::vec3& end) {
        return (end.x - start.x) / (end.y - start.y);
    }

float rtr::Device::ZXslope(const glm::vec3& start, const glm::vec3& end) {
    return (end.z - start.z) / (end.x - start.x); 
}

float rtr::Device::ZYslope(const glm::vec3&start, const glm::vec3& end) {
    return (end.z - start.z) / (end.y - start.y);
}

float rtr::Device::Clamp(float value, float min, float max) {
    return std::fmax(min, std::fmin(value, max));
}


float rtr::Device::Interpolate(float min, float max, float gradient) {
    return min + (max - min) * Clamp(gradient);
}