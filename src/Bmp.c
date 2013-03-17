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
#include <sys/stat.h>
#include "Bmp.h"

FILE *bmpFileIn;
FILE *bmpFileOut;

int paddingBytes;


/* Calculates the padding bytes for the read bmp
 * @params: width - width of the read bmp
 */

int static calculatePaddingBytes(int width) {
	int padding = (4-(3*width) % 4) % 4;
	return padding;
}

/* gets the size of the file on the actual system
 * @params: fileName - name of the file to be read.
 */

long static getFileSize(char *fileName) {
	struct stat fileStat;
	if (stat(fileName, &fileStat) != 0) {
		ErrorExit(EXIT_FAILURE, "Error determining file size.");
	}
	long fileSize = (long)fileStat.st_size;
	return fileSize;
}

/* Calculates the fileSize from the information read  
 * into the bmpInfoHeader
 */

static long calculateBmpFileSize() {
	long bmpFileSize = bmpInfoHeader.height * (3 * bmpInfoHeader.width + paddingBytes) + 54;
	return bmpFileSize;
}

void readBmpHeaders(char * fileName) {	
	byte bufferHeader[sizeof(tBmpHeader)];	
	bmpFileIn = fopen(fileName, "rb");

	long fileSize;
	long bmpFileSize;

	if (bmpFileIn == NULL) {
		ErrorExit(EXIT_FAILURE, "The file could not be opened");
	}

	if (fread(bufferHeader, 14, 1, bmpFileIn) != 1) {
		ErrorExit(EXIT_FAILURE, "Error reading File");
	}

	if(bufferHeader[0] != 'B' || bufferHeader[1] != 'M') {
		ErrorExit(EXIT_FAILURE, "Not a BMP File");
	}

	// using a buffer to avoid struct packing issues

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

	paddingBytes = calculatePaddingBytes(bmpInfoHeader.width);

	printf("paddingBytes: %d\n", paddingBytes);

	fileSize = getFileSize(fileName);
	bmpFileSize = calculateBmpFileSize();

	printf("File Size: %ld\n", fileSize);
	printf("bmpFileSize: %ld\n", bmpFileSize);
	printf("bits per pixel: %d\n", bmpInfoHeader.bitsPerPixel);

	if (bmpInfoHeader.bitsPerPixel != 24) {
		ErrorExit(EXIT_FAILURE, "This program only supports 24 bit pixels");
	}

	if (fileSize != bmpFileSize) {
		printf("%s is corrupted\n", fileName);
		exit(EXIT_FAILURE);
	}

}

/*****************************
* Initializes the 2D array of pixels
* and reads the actual file pixels into the array
*****************************/

tPixel **readBmpPixels() {
	
	int height = bmpInfoHeader.height;
	int width = bmpInfoHeader.width;

	pixels = (tPixel **) malloc(height * sizeof(tPixel *));
	for (int row = 0; row < height; row++) {
		pixels[row] = (tPixel *) malloc(width * sizeof(tPixel));
		
	}
	
	printf("Width: %d\n", bmpInfoHeader.width);
	printf("Height: %d\n", bmpInfoHeader.height);	

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if(fread(&pixels[row][col], 3, 1, bmpFileIn) != 1) {
				ErrorExit(EXIT_FAILURE, "Pixel Error.");
			}
			fseek(bmpFileIn, (long)paddingBytes, SEEK_CUR);			
		}
 	}
 	
	return pixels;
}

/* Writes the processed bmp file
 * @params: fileName - name of file to be written
 * 			pixelsToWrite - the processed image pixels
 */

void writeBmp(char *fileName, tPixel **pixelsToWrite) {
	int height = bmpInfoHeader.height;
	int width = bmpInfoHeader.width;

	char *padding = "\0\0\0\0";

	paddingBytes = calculatePaddingBytes(width);

	printf("Updated paddingBytes: %d\n", paddingBytes);

	bmpFileOut = fopen("../image.bmp", "wb");
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

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if(fwrite(&padding, 1, paddingBytes, bmpFileOut) != paddingBytes) {
				ErrorExit(EXIT_FAILURE, "Error writing padding");
			}	
			if(fwrite(&pixelsToWrite[row][col], 3, 1, bmpFileOut) != 1) {
				ErrorExit(EXIT_FAILURE, "Error writing file 3");
			}
			
		}
 	}

 	fclose(bmpFileOut);
 	
}	

