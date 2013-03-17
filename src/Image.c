#include "Image.h"

/* rotates image n % 4 times clockwise
 * @params: bmpToRot - pixels to be rotated
 *			n - number of times to rotate
 * Returns: rotated bmp pixels
 */

tPixel ** rotateBmp(tPixel** bmpToRot, int n) {
	const int M = bmpInfoHeader.height;
	const int N = bmpInfoHeader.width;

	if (n % 4 == 0) {
		return bmpToRot;	
	}

	tPixel **newBmp = (tPixel**)malloc(N * sizeof(tPixel*));
	for (int i = 0; i < N; i++) {
		newBmp[i] = (tPixel*)malloc(M * sizeof(tPixel));
	}

	for(int r = 0; r < M; r++) {
		for (int c = 0; c < N; c++) {
			newBmp[c][M-1-r] = bmpToRot[r][c];
		}
	}

	updateBmpInfo(M, N);

	return newBmp;
}

/* updates the bmpInfoHeader with new information
 * Params: newWidth - the new width of the bmp
 * 		   new Height - the new height of the bmp
 */

void updateBmpInfo(int newWidth, int newHeight) {
	bmpInfoHeader.width = newWidth;
	bmpInfoHeader.height = newHeight;
}