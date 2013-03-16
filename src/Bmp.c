/***************************************************************************************************************
 * FILE: Read.c
 *
 * DESCRIPTION
 * Reads Bmp file and checks for errors
 *
 * AUTHOR INFORMATION
 * Brian Blanchard and Brittney Russell
 *
 **************************************************************************************************************/
#include "Bmp.h"

void readBmpHeaders(tCmdLine *cmdArgs) {	
	byte bufferHeader[sizeof(tBmpHeader)];	
	bmpFileIn = fopen(cmdArgs->inFile, "rb");

	if (bmpFileIn == NULL) {
		ErrorExit(EXIT_FAILURE, "The file could not be opened");
	}

	if (fread(bufferHeader, 14, 1, bmpFileIn) != 1) {
		ErrorExit(EXIT_FAILURE, "Error reading File");
	}

	if(bufferHeader[0] != 'B' || bufferHeader[1] != 'M') {
		ErrorExit(EXIT_FAILURE, "Not a BMP File");
	}

	bmpHeader.signature_B = bufferHeader[0];
	bmpHeader.signature_M = bufferHeader[1];
	memcpy(&bmpHeader.fileSize, &bufferHeader[2], sizeof(bmpHeader.fileSize));
	memcpy(&bmpHeader.reserved1, &bufferHeader[6], sizeof(bmpHeader.reserved1));
	memcpy(&bmpHeader.reserved2, &bufferHeader[8], sizeof(bmpHeader.reserved2));
	memcpy(&bmpHeader.pixelOffset, &bufferHeader[10], sizeof(bmpHeader.pixelOffset));

	printf("Size of tBmpInfoHeader: %ld\n", sizeof(tBmpInfoHeader));

	if(fread(&bmpInfoHeader, sizeof(tBmpInfoHeader), 1, bmpFileIn) != 1) {
		ErrorExit(EXIT_FAILURE, "Error reading File");
	}	
}

tPixel **readBmpPixels(tCmdLine *cmdArgs) {
	/*****************************
	* Initializes the 2D array of pixels
	* and reads the actual file pixels into the array
	*****************************/

	pixels = (tPixel **) malloc(bmpInfoHeader.height * sizeof(tPixel *));
	for (int row = 0; row < bmpInfoHeader.height; row++) {
		pixels[row] = (tPixel *) malloc(bmpInfoHeader.width * sizeof(tPixel));
		
	}
	
	printf("Width: %d\n", bmpInfoHeader.width);
	printf("Height: %d\n", bmpInfoHeader.height);	

	for (int row = 0; row < bmpInfoHeader.height; row++) {
		for (int col = 0; col < bmpInfoHeader.width; col++) {
			if(fread(&pixels[row][col], 3, 1, bmpFileIn) != 1) {
				ErrorExit(EXIT_FAILURE, "Pixel Error.");
			}

		}
 	}
 	
	return pixels;

}

void testWrite(tCmdLine *cmpArgs) {
	bmpFileOut = fopen("image.bmp", "wb");
	if(bmpFileOut == NULL) {
		ErrorExit(EXIT_FAILURE, "The file could not be opened.");
	}
	byte bufferHeader[sizeof(tBmpHeader)];

	bufferHeader[0] = bmpHeader.signature_B;
	bufferHeader[1] = bmpHeader.signature_M;
	memcpy(&bufferHeader[2], &bmpHeader.fileSize, sizeof(bmpHeader.fileSize));
	memcpy(&bufferHeader[6], &bmpHeader.reserved1, sizeof(bmpHeader.reserved1));
	memcpy(&bufferHeader[8], &bmpHeader.reserved2, sizeof(bmpHeader.reserved2));
	memcpy(&bufferHeader[10], &bmpHeader.pixelOffset, sizeof(bmpHeader.pixelOffset));

	if(fwrite(bufferHeader, 14, 1, bmpFileOut) != 1) {
		ErrorExit(EXIT_FAILURE, "Error writing file 1");
	}

	if(fwrite(&bmpInfoHeader, 40, 1, bmpFileOut) != 1) {
		ErrorExit(EXIT_FAILURE, "Error writing file 2");
	}

	for (int row = 0; row < bmpInfoHeader.height; row++) {
		for (int col = 0; col < bmpInfoHeader.width; col++) {
			if(fwrite(&pixels[row][col], 3, 1, bmpFileOut) != 1) {
				ErrorExit(EXIT_FAILURE, "Pixel Write Error.");
			}
		}
 	}

 	fclose(bmpFileOut);
}	

