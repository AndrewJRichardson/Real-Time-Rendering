#include "RasterizeFilled.h"
#include <cmath>

 void rtr::RasterizeFilled::operator()(FaceVertSet pointA, FaceVertSet pointB,
                                       FaceVertSet pointC, Device& device,
                                       const Object& object) {
    
    if (pointA.v.z >= 2 && pointB.v.z >= 2 && pointC.v.z >= 2)
        device.RenderTriangle(pointA.v, pointB.v, pointC.v);
}
// }
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
    

//     float invAB;
//     float invAC;
//     float invBC;

//     if (pointB.y - pointA.y <= 0)
//         invAB = 0;
//     else
//         invAB = device.InverseSlope(pointA, pointB);

//     if (pointC.y - pointA.y <= 0)
//         invAC = 0;
//     else
//         invAC = device.InverseSlope(pointA, pointC);

//     if (pointC.y - pointB.y <= 0)
//         invBC = 0;
//     else
//         invBC = device.InverseSlope(pointB, pointC);



//     glm::vec3 t1 {1, 1, 1};
//     glm::vec3 t2 {1, 7, 2};
//     glm::vec3 t3 {7, 9, 3};

//     float X  = device.InterpolateX(pointA, pointB, pointC, pointA.x, pointB.x, pointC.x);
//     float Y  = device.InterpolateY(pointA, pointB, pointC, pointA.y, pointB.y, pointC.y);
//     float xZ = device.InterpolateX(pointA, pointB, pointC, pointA.z, pointB.z, pointC.z);
//     float yZ = device.InterpolateY(pointA, pointB, pointC, pointA.z, pointB.z, pointC.z);

//     float xZinc;
//     if (X == 0)
//         xZinc = 0;
//     else
//         xZinc = xZ/X;
//     float yZinc = yZ/Y;

//     float zYAB = yZinc + xZinc * invAB;
//     float zYAC = yZinc + xZinc * invAC;
//     float zYBC = yZinc + xZinc * invBC;

//     float ABx = pointA.x;
//     float ACx = pointA.x;
//     float BCx = pointB.x;

//     float ABz = pointA.z; //+ xZinc + yZinc;
//     float ACz = pointA.z; // + xZinc + yZinc;
//     float BCz = pointB.z; //+ xZinc + yZinc;    

    


//     bool leftB = false;
//     if(device.SignedArea(pointA, pointB, pointC) < 0)
//         leftB = true;

//     // for (int i = (int)pointA.y; i < (int)pointC.y -1 ; i++){
//     //         if(i < pointB.y - 1){
//     //             if(leftB){
//     //                 device.DrawScanLine(i, (int)ABx, (int)ACx, ABz, depStepAB, 0, 0xff, 0xff, 0xff);
//     //                 ABz += depStepAB;
//     //             }else{
//     //                 device.DrawScanLine(i, (int)ACx, (int)ABx, ACz, depStepAC, 0, 0xff, 0, 0);
//     //                 ACz += depStepAC;
//     //             }
//     //             ABx += invAB;
//     //         }else{
//     //             if(leftB){
//     //                 device.DrawScanLine(i, (int)BCx, (int)ACx, BCz, zXinc, 0, 0xff, 0xff, 0xff);
//     //                 BCz += depStepBC;
//     //             }else{
//     //                 device.DrawScanLine(i, (int)ACx, (int)BCx, ACz, zXinc, 0, 0xff, 0, 0);
//     //                 ACz += depStepAC;
//     //             }
//     //             BCx += invBC;
//     //         }
//     //         ACx += invAC;
//     // }

//     for (int i = (int)pointA.y; i < (int)pointC.y -1; i++){
//             if(i < pointB.y - 1){
//                 if(leftB){
//                     device.DrawScanLine(i, (int)ABx, (int)ACx, ABz, ACz, 0xff, 0xff, 0xff);
//                 }else{
//                     device.DrawScanLine(i, (int)ACx, (int)ABx, ACz, ABz, 0, 0, 0xff);
//                 }
//                 ABz += zYAB;
//                 ABx += invAB;
//             }else{
//                 if(leftB){
//                     device.DrawScanLine(i, (int)BCx, (int)ACx, BCz, ACz, 0, 0xff, 0);
//                 }else{
//                     device.DrawScanLine(i, (int)ACx, (int)BCx, ACz, BCz, 0xff, 0, 0);
//                 }
//                 BCz += zYBC;
//                 BCx += invBC;
//             }
//             ACz += zYAC;
//             ACx += invAC;
//     }
// }

