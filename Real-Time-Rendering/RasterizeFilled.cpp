#include "RasterizeFilled.h"
#include <cmath>

rtr::RasterizeFilled::RasterizeFilled() {}

rtr::RasterizeFilled::RasterizeFilled(SDL_Window& window) : window (&window){colour = true; c = 0;}


void rtr::RasterizeFilled::operator()(FaceVertSet pointA, FaceVertSet pointB,
                                      FaceVertSet pointC, Device& device) {
    
   device.RenderTriangle(pointA.v, pointB.v, pointC.v);
}
// int r = 0x00, g = 0x00, b = 0x00;

// c++;
// switch (c){
//     case 0:
//         r = 0xff;
//         break;
//     case 1:
//         b = 0xff;
//         break;
//     case 2:
//         g = 0xff;
//         break;
//     case 3:
//         r = 0xff;
//         b = 0xff;
//     case 4:
//         r = 0xff;
//         break;
//     case 5:
//         b = 0xff;
//         g = 0xff;
//         break;
//     case 6:
//         r = 0xff;
//         g = 0xff;
//         c = 0;
//         break;
// }
// colour = !colour;
// if(colour){
//     r = 0xFF; 
//     g = 0x00; 
//     b = 0x00;
// }

//     if (pointA.y > pointB.y) {
//         glm::vec3 tPoint = pointB;
//         pointB = pointA;
//         pointA = tPoint;
//     }

//     if (pointB.y > pointC.y) {
//         glm::vec3 tPoint = pointC;
//         pointC = pointB;
//         pointB = tPoint;
//     }

//     if (pointA.y > pointB.y) {
//         glm::vec3 tPoint = pointB;
//         pointB = pointA;
//         pointA = tPoint;
//     }

//     float invAB = 0, invAC = 0, invBC = 0, zxAB = 0, zxAC = 0, zxBC = 0,
//           zyAB  = 0,  zyAC = 0, zyBC  = 0;

//     bool right = false, left = false;

//     if ((int)(pointB.y - pointA.y) > 0){
//         invAB = device.InverseSlope(pointA, pointB);
//     }
//    if (pointB.x > pointA.x) {
//         right = true;
//         //invAB = 1;
//     }
//     else {
//         left = true;
//         //invAB = -1;
//     }

//     //A and C having the same y should be a very rare case
//     //but it still needs to be dealt with
//     if (pointC.y - pointA.y > 0) {
//         invAC = device.InverseSlope(pointA, pointC);
//     }
    
//     if (pointC.y - pointB.y > 0) {
//         invBC = device.InverseSlope(pointB, pointC);
//     }


//     if((int)pointA.y != (int)pointB.y){
//         zyAB = device.ZYslope(pointA, pointB);
//     } 
//     if (((int)pointB.x != (int)pointA.x) != 0){
//         zxAB = device.ZXslope(pointA, pointB);
//     }
//     if(((int)pointC.x != (int)pointA.x)){
//         zxAC = device.ZXslope(pointA, pointC);
//     }
//     if(((int)pointC.y != (int)pointA.y)){
//         zyAC = device.ZYslope(pointA, pointC);
//     }


//     if(((int)pointC.x != (int)pointB.x)){
//         zxBC = device.ZXslope(pointB, pointC);
//     }
//     if(((int)pointC.y != (int)pointB.y)){
//         zyBC = device.ZYslope(pointB, pointC);
//     }
    
//     float ABx    = pointA.x;
//     float ACx    = pointA.x;
//     float BCx    = pointB.x;
//     float ABz    = pointA.z;
//     float ACz    = pointA.z;
//     float BCz    = pointB.z;
//     float ACzy   = pointA.z;
//     float ABzy   = pointA.z;
//     float BCzy   = pointB.z;

    
//     if(pointB.y == pointA.y){
//         invAB = 1;
//     }
//     if(pointC.y == pointB.y){
//          invBC = 1;
//     }
    

    
//     // if(pointB.z == pointA.z){
//     //     zxAB = 0;
//     //     zyAB = 0;
//     // }
//     // if(pointA.z == pointC.z){
//     //     zxAC = 0;
//     //     zyAC = 0;
//     // }
//     // if(pointB.z == pointC.z){
//     //     zxBC = 0;
//     //     zyBC = 0;
//     // }

    
//     if (right || (!left && invAB > invAC)) {
        
//         for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {
//             if (y < (int)pointB.y) {
//                 device.DrawScanLine(y, (int)ACx, (int)ABx, ACz, zxAB - zyAC, ACz, r, g, b);
//                 ABx += invAB;
//             }
//             else {
//                 device.DrawScanLine(y, (int)ACx, (int)BCx, ACz, zxBC - zyAC, ACz, r, g, b);
//                 BCx += invBC;
//             }
//             // SDL_UpdateWindowSurface(window);
//             ACx += invAC; 
//             ACz += zyAC;
//         }
//     }
    // else {
    //     for (int y = (int)pointA.y; y <= (int)pointC.y; y++) {

    //         if (y < (int)pointB.y) {
    //             device.DrawScanLine(y, (int)ABx, (int)ACx, pointA.z, zxAB + zyAC, ABz, r, g, b);
    //             ABx += invAB;
    //             ABz += zyAB;
    //         }
    //         else {
    //             device.DrawScanLine(y, (int)BCx, (int)ACx, , zxBC - zyAC, BCz, r, g, b);
    //             BCx += invBC; 
    //             BCz += zyBC;
    //         }
    //         // SDL_UpdateWindowSurface(window);
    //         ACx += invAC;
    //     }
    // }
// }

// void rtr::RasterizeFilled::operator()(FaceVertSet faceA, FaceVertSet faceB,
//                                       FaceVertSet faceC, Device& device) {

//     glm::vec3 pointA = faceA.v;
//     glm::vec3 pointB = faceB.v;
//     glm::vec3 pointC = faceC.v;
    
//      if (pointA.y > pointB.y) {
//         glm::vec3 tPoint = pointB;
//         pointB = pointA;
//         pointA = tPoint;
//     }

//     if (pointB.y > pointC.y) {
//         glm::vec3 tPoint = pointC;
//         pointC = pointB;
//         pointB = tPoint;
//     }

//     if (pointA.y > pointB.y) {
//         glm::vec3 tPoint = pointB;
//         pointB = pointA;
//         pointA = tPoint;
//     }
    
//     float invAB = device.InverseSlope(pointA, pointB);
//     float invAC = device.InverseSlope(pointA, pointC);
//     float invBC = device.InverseSlope(pointB, pointC);

//     float ABx = pointA.x;
//     float ACx = pointA.x;
//     float BCx = pointB.x;
//     float ABz = pointA.z;
//     float ACz = pointA.z;
//     float BCz = pointB.z;

//     glm::vec3 a{1,2,4};
//     glm::vec3 t{2,4,2};
//     glm::vec3 c{0,6,1};

//     float testt = device.XInterpolant(a, t, c, a.z, t.z, c.z);
//     float t2    = device.YInterpolant(a, t, c, a.z, t.z, c.z);
//     float zXinc = device.XInterpolant(pointA, pointB, pointC, 
//                             pointA.z, pointB.z, pointC.z);
    
//     float zTest = device.YInterpolant(pointA, pointB, pointC, pointA.z, pointB.z, pointC.z);
//     float zYinc = -zXinc;


//     bool leftB = false;
//     if(device.SignedArea(pointA, pointB, pointC) < 0)
//         leftB = true;

//     for (int i = (int)pointA.y; i < (int)pointC.y -1 ; i++){
//             if(i < pointB.y - 1){
//                 if(leftB){
//                     device.DrawScanLine(i, (int)ABx, (int)ACx, ABz, zXinc, 0, 0xff, 0xff, 0xff);
//                     ABz += zYinc;
//                 }else{
//                     device.DrawScanLine(i, (int)ACx, (int)ABx, ACz, -zXinc, 0, 0xff, 0, 0);
//                     ACz += zYinc;
//                 }
//                 ABx += invAB;
//             }else{
//                 if(leftB){
//                     device.DrawScanLine(i, (int)BCx, (int)ACx, BCz, zXinc, 0, 0, 0xff, 0);
//                     BCz += zYinc;
//                 }else{
//                     device.DrawScanLine(i, (int)ACx, (int)BCx, ACz, -zXinc, 0, 0, 0, 0xff);
//                     ACz += zYinc;
//                 }
//                 BCx += invBC;
//             }
//             ACx += invAC;
//     }
// }

