#include <stdio.h>
#include "Bmp.h"



tPixel** rotateBmp(tPixel **bmpToRot){
	
	int m = bmpInfoHeader.width; // colomuns
	int n = bmpInfoHeader.height; //rows

	bmpToRot = (tPixel **)malloc(n * sizeof(tPixel *));
	for(int row = 0; row < n; row++){
		bmpToRot[row] = (tPixel *)malloc(m * sizeof(tPixel));
	}

	for(int c = 0; c < m; c++){
		for(int r = 0; r < n; r++){
			bmpToRot[n][m-1-c]=bmpToRot[m][n];
		}
	}

	bmpInfoHeader.width = n;
	bmpInfoHeader.height = m;

	return bmpToRot;
}


tPixel** flipBmpHoriz(tPixel **bmpToHorFlip){
	int m = bmpInfoHeader.width; // colomuns
	int n = bmpInfoHeader.height;
	tPixel temp;

	for(int row = 0; row < n; row++){
		for(int col = 0; col < m; col++){
			temp = bmpToHorFlip[row][col];
			bmpToHorFlip[row][col] = bmpToHorFlip[row][m-col-1];
			bmpToHorFlip[row][m-col-1] = temp;
		}
	}

	return bmpToHorFlip;
}

tPixel ** flipBmpVer(tPixel **bmpToFlipVer){
	int m = bmpInfoHeader.width;
	int n = bmpInfoHeader.height;
	tPixel temp;

	for(int col = 0; col < m; col++){
		for(int row = 0; row < n; row++){
			temp = bmpToFlipVer[row][col];
			bmpToFlipVer[row][col] = bmpToFlipVer[n-row-1][col];
			bmpToFlipVer[n-row-1][col] = temp;
		}
	}
}