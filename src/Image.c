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

	printf("%d\n", n);

	if ((timesToRot = n % 4) == 0) {
		return bmpToRot;	
	}
	else {
		tPixel **newBmp = (tPixel**)malloc(N * sizeof(tPixel*));
		for (int i = 0; i < N; i++) {
			newBmp[i] = (tPixel*)malloc(M * sizeof(tPixel));
		}		
		
		printf("hit\n");

		for(int r = 0; r < M; r++) {
			for (int c = 0; c < N; c++) {				
				newBmp[c][r] = bmpToRot[r][N-1-c];
			}
		}

		updateBmpInfo(M, N);
		return rotateBmp(newBmp, n-1);				
	}
	
}

/* updates the bmpInfoHeader with new information
 * Params: newWidth - the new width of the bmp
 * 		   newHeight - the new height of the bmp
 */

void updateBmpInfo(int newWidth, int newHeight) {
	bmpInfoHeader.width = newWidth;
	bmpInfoHeader.height = newHeight;
}

