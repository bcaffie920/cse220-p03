#ifndef IMAGE_H
#define IMAGE_H
#include "Bmp.h"

//function declarations
tPixel **rotateBmp(tPixel**, int);
tPixel** flipBmpHoriz(tPixel **);
tPixel ** flipBmpVer(tPixel **);
void updateBmpInfo(int, int);



#endif