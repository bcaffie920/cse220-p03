#ifndef IMAGE_H
#define IMAGE_H
#include "Bmp.h"
//function declarations
tPixel **rotateBmp(tPixel**, int);
tPixel** flipBmpHoriz(tPixel **);
tPixel ** flipBmpVer(tPixel **);
tPixel **flipVert(tPixel **bmpToFlip);
void updateBmpInfo(int, int);

#endif