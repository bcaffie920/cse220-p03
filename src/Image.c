#include "Image.h"

/* rotates image n % 4 times clockwise
 * @params: bmpToRot - pixels to be rotated
 *			n - number of times to rotate
 * Returns: rotated bmp pixels
 */

tPixel ** rotateBmp(tPixel** bmpToRot, int n) {
	int M = bmpInfoHeader.height;
	int N = bmpInfoHeader.width;
	int timesToRot;

	if ((timesToRot = n % 4) == 0) {
		return bmpToRot;	
	}
	else {
		tPixel **newBmp = (tPixel**)malloc(N * sizeof(tPixel*));
		for (int i = 0; i < N; i++) {
			newBmp[i] = (tPixel*)malloc(M * sizeof(tPixel));
		}		

		for(int r = 0; r < M; r++) {
			for (int c = 0; c < N; c++) {				
				newBmp[c][r] = bmpToRot[r][N-1-c];
			}
		}

		updateBmpInfo(M, N);
		return rotateBmp(newBmp, n-1);				
	}
	
}

tPixel** flipBmpHoriz(tPixel **bmpToHorFlip){
	int rows  = bmpInfoHeader.height;
	int cols = bmpInfoHeader.width;
	tPixel temp;
	
	for (int i = 0; i < rows; i++) {
		for(int j = 0; j< cols/2; j++) {
			temp = bmpToHorFlip[i][j];
			bmpToHorFlip[i][j] = bmpToHorFlip[i][cols-(j+1)];
			bmpToHorFlip[i][cols-(j+1)] = temp;
		}
	}

	return bmpToHorFlip;
}

tPixel ** flipBmpVer(tPixel **bmpToFlipVer){
	int rows  = bmpInfoHeader.height;
	int cols = bmpInfoHeader.width;
	tPixel temp;
	
	for (int i = 0; i < rows/2; i++) {
		for(int j = 0; j< cols; j++) {
			temp = bmpToFlipVer[i][j];
			bmpToFlipVer[i][j] = bmpToFlipVer[rows-(i+1)][j];
			bmpToFlipVer[rows-(i+1)][j] = temp;
		}
	}

	return bmpToFlipVer;
}


/* updates the bmpInfoHeader with new information
 * Params: newWidth - the new width of the bmp
 * 		   newHeight - the new height of the bmp
 */

void updateBmpInfo(int newWidth, int newHeight) {
	bmpInfoHeader.width = newWidth;
	bmpInfoHeader.height = newHeight;
}

