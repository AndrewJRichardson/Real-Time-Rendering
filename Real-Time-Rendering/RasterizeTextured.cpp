#include "RasterizeTextured.h"


void rtr::RasterizeTextured::operator()(FaceVertSet a, FaceVertSet b, FaceVertSet c,
                                        Device& device, const Object& object){
    if (a.v.x < 0 || a.v.x > device.bufferWidth ||
        b.v.x < 0 || b.v.x > device.bufferWidth ||
        c.v.x < 0 || c.v.x > device.bufferWidth ||
        a.v.y < 0 || a.v.y > device.bufferHeight ||
        b.v.y < 0 || b.v.y > device.bufferHeight ||
        c.v.y < 0 || c.v.y > device.bufferHeight){ 
            return;
        }



    if (a.v.z <= 2 || b.v.z <=2 || c.v.z <=2)
        return;

   
     if (a.v.y > b.v.y) {
        FaceVertSet tPoint = b;
        b = a;
        a = tPoint;
    }

    if (b.v.y > c.v.y) {
        FaceVertSet tPoint = c;
        c = b;
        b = tPoint;
    }

    if (a.v.y > b.v.y) {
        FaceVertSet tPoint = b;
        b = a;
        a = tPoint;
    }
    
    float invAB = 0, invAC = 0, invBC = 0;

    if (b.v.y - a.v.y > 0)
        invAB = device.InverseSlope(a.v, b.v);

    if (c.v.y - a.v.y > 0)
        invAC = device.InverseSlope(a.v, c.v);

    if (c.v.y - b.v.y > 0)
        invBC = device.InverseSlope(b.v, c.v);

    float gAB, gBC, gAC, 
          gradAB = 0, gradBC = 0, gradAC = 0;

    if (a.v.y != b.v.y)
        gAB = 1/(b.v.y - a.v.y);
    else
        gAB = 1;

    if(a.v.y != c.v.y)
        gAC = 1/(c.v.y - a.v.y);
    else
        gAC = 1;
    
    if(b.v.y != c.v.y)
        gBC = 1/(c.v.y - b.v.y);
    else
        gBC = 1;


    float ABx = a.v.x, ACx = a.v.x, BCx = b.v.x;


    bool leftB = false;
    if(device.SignedArea(a.v, b.v, c.v) < 0)
        leftB = true;


    for (int i = (int)a.v.y; i < (int)c.v.y; i++){
            if(i < b.v.y - 1){
                if(leftB)
                    device.DrawScanLineTexture(i, (int)ABx, (int)ACx, a, b, a, 
                        c, object, gradAB, gradAC);
                else
                    device.DrawScanLineTexture(i, (int)ACx, (int)ABx, a, c, a,
                        b, object, gradAC, gradAB);
                gradAB += gAB;
                ABx += invAB;
            }else{
                if(leftB)
                    device.DrawScanLineTexture(i, (int)BCx, (int)ACx, b, c, a,
                        c, object, gradBC, gradAC);
                else
                    device.DrawScanLineTexture(i, (int)ACx, (int)BCx, a, c, b,
                        c, object, gradAC, gradBC);
                gradBC += gBC;
                BCx += invBC;
            }
            gradAC += gAC;
            ACx += invAC;
    }

}