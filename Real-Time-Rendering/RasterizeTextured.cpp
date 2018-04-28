#include "RasterizeTextured.h"


void rtr::RasterizeTextured::Render(FaceVertSet a, FaceVertSet b, FaceVertSet c,
                                    Device& device, const Object& object){
    
    
    if (a.v.y > b.v.y) {
        FaceVertSet tSet = b;
        b = a;
        a = tSet;
    }

    if (b.v.y > c.v.y) {
        FaceVertSet tSet = c;
        c = b;
        b = tSet;
    }

    if (a.v.y > b.v.y) {
        FaceVertSet tSet = b;
        b = a;
        a = tSet;
    }

    float invAB, invAC;

    if (b.v.y - a.v.y > 0) {
        invAB = device.InverseSlope(a.v, b.v);
    } else {
        invAB = 0;
    }

    if (c.v.y - a.v.y > 0) {
        invAC = device.InverseSlope(a.v, c.v);
    } else {
        invAC = 0;
    }

    bool right = false, left = false;

    if (b.v.y - a.v.y > 0) {
        invAB = device.InverseSlope(a.v, b.v);
    }
    else if (b.v.x > a.v.x) {
        right = true;
    }
    else {
        left = true;
    }
    
    float gAB, gBC, gAC, 
          gZ = 0,
          gABB = 0, gBCC = 0, gACC = 0;

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

    // gABz = device.Interpolate(a.v.x, b.v.x, gAB);
    // gACz = device.Interpolate(a.v.x, c.v.x, gAC);
    // gBCz = device.Interpolate(b.v.x, c.v.x, gBC);
    
    if (right || (!left && invAB > invAC)) {
        for (int y = (int)a.v.y; y <= (int)c.v.y; y++) {
            if (y < b.v.y) {
                device.DrawScanLineTexture(y, a, c, a, b, object, gACC, gABB, gZ);
                gABB += gAB;
            }
            else {
                device.DrawScanLineTexture(y, a, c, b, c, object, gACC, gBCC, gZ);
                gBCC += gBC;
            }
            gACC += gAC;
        }
    }
    else {
        for (int y = (int)a.v.y; y <= (int)c.v.y; y++) {
            if (y < b.v.y) {
                device.DrawScanLineTexture(y, a, b, a, c, object, gABB, gACC, gZ);
                gABB += gAB;
            }
            else {
                device.DrawScanLineTexture(y, b, c, a, c, object, gBCC, gACC, gZ);
                gBCC += gBC;
            }
            gACC += gAC;
        }
    }


}