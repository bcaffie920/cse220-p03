#ifndef BMP_H
#define BMP_H

#include <stdbool.h>  // For bool data type
#include <stdio.h>    // For printf()
#include <stdlib.h>   // For exit(), strtod()
#include <stdint.h>

//==============================================================================================================
// TYPE DEFINITIONS
//==============================================================================================================

typedef uint8_t byte;

typedef struct {
	char 	signature_B;
	char 	signature_M;
	int32_t fileSize;
	int16_t reserved1;
	int16_t reserved2;
	int32_t pixelOffset;
} tBmpHeader;

typedef struct {
	int32_t sizeBmpInfoHeader;
	int32_t width;
	int32_t height;
	int16_t bitPlanes;
	int16_t bitsPerPixel;
	byte 	zeros[24];
} tBmpInfoHeader;


typedef struct {
    byte blue;
    byte green;
    byte red;
} tPixel;

tBmpHeader bmpHeader;
tBmpInfoHeader bmpInfoHeader;

/***********************
* Function Declerations
***********************/
void readBmpHeaders(char *fileName);
tPixel **readBmpPixels();
void writeBmp(char *fileName, tPixel **);
#endif