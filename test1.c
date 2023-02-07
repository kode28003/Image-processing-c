#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include"pgmlib.h"

#define HIGH   255	
#define LOW      0	

void normalBinarize(int n);
void binarize(int n);
void gradient(int n);
void moveAve(int n);
void erosion(int n);
void expantion(int n);


int main(void) {
	load_image(0, "C:\\Users\\Downloads\\image\\in.pgm");
	gradient(0);
	normalBinarize(0);
	moveAve(0);
	
	save_image(0, "C:\\Users\\Downloads\\image\\out.pgm");
	return 0;
}
int main(void) {
	load_image(0, "C:\\Users\\Downloads\\image\\in.pgm");
	gradient(0);
	normalBinarize(0);
	//moveAve(0);
	load_image(1, "C:\\UsersDownloads\\image\\in.pgm");
	gradient(1);
	normalBinarize(1);
	//moveAve(1);
	erosion(0);
	erosion(1);
	expantion(0);



	save_image(0, "C:\\Users\\Downloads\\image\\out.pgm");
	save_image(1, "C:\\Users\\Downloads\\image\\nnn.pgm");
	return 0;
}

void expantion(int n) {
	int    i, j;
	for (i = 1; i < height[n]; i++) {
		for (j = 1; j < width[n]; j++) {
			image[n+1][i][j] = image[n][i][j];
			if (image[n+1][i - 1][j - 1] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i - 1][j] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i - 1][j + 1] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i][j - 1] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i][j + 1] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i + 1][j - 1] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i + 1][j] == HIGH) image[n][i][j] = HIGH;
			if (image[n + 1][i + 1][j + 1] == HIGH) image[n][i][j] = HIGH;
		}
	}
}

void erosion(int n) {
	int    i, j;
	for (i = 1; i < height[n]; i++) {
		for (j = 1; j < width[n]; j++) {
			image[n + 1][i][j] = image[n][i][j];
			if (image[n + 1][i - 1][j - 1] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i - 1][j] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i - 1][j + 1] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i][j - 1] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i][j + 1] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i + 1][j - 1] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i + 1][j] == LOW) image[n][i][j] = LOW;
			if (image[n + 1][i + 1][j + 1] == LOW) image[n][i][j] = LOW;
		}
	}
}


void gradient(int n)
{
	static int cx[9] = { 0, 0, 0,    
						 0, 1, 0,  
						 0, 0,-1 };   
	static int cy[9] = { 0, 0, 0,   
						 0, 0, 1,    
						 0,-1, 0 };   
	int        d[9];
	int        i, j, dat;
	float    xx, yy, zz;

	for (i = 1; i < height[n]; i++) {
		for (j = 1; j < width[n]; j++) {
			d[0] = image[n][i - 1][j - 1];
			d[1] = image[n][i - 1][j];
			d[2] = image[n][i - 1][j + 1];
			d[3] = image[n][i][j - 1];
			d[4] = image[n][i][j];
			d[5] = image[n][i][j + 1];
			d[6] = image[n][i + 1][j - 1];
			d[7] = image[n][i + 1][j];
			d[8] = image[n][i + 1][j + 1];
			xx = (float)(cx[0] * d[0] + cx[1] * d[1] + cx[2] * d[2]
				+ cx[3] * d[3] + cx[4] * d[4] + cx[5] * d[5]
				+ cx[6] * d[6] + cx[7] * d[7] + cx[8] * d[8]);
			yy = (float)(cy[0] * d[0] + cy[1] * d[1] + cy[2] * d[2]
				+ cy[3] * d[3] + cy[4] * d[4] + cy[5] * d[5]
				+ cy[6] * d[6] + cy[7] * d[7] + cy[8] * d[8]);
			zz = (float)(1 * sqrt(xx * xx + yy * yy));
			dat = (int)zz;
			if (dat > 255) dat = 255;
			image[n][i][j] = (char)dat;
		}
	}
}

void moveAve(int n)//3×3
{
	int i, j, buf;

	for (i = 1; i < height[n]; i++) {
		for (j = 1; j < width[n]; j++) {
			buf = (int)image[n][i - 1][j - 1]
				+ (int)image[n][i - 1][j]
				+ (int)image[n][i - 1][j + 1]
				+ (int)image[n][i][j - 1]
				+ (int)image[n][i][j]
				+ (int)image[n][i][j + 1]
				+ (int)image[n][i + 1][j - 1]
				+ (int)image[n][i + 1][j]
				+ (int)image[n][i + 1][j + 1];
			image[n][i][j] = buf / 9;
		}
	}
}


void binarize(int n) {
	int thvalueDark = 135; 
	int thvalueBright = 170;//170
	int x0=430;
	int y0=250;
	int x1=800;
	int y1=730;
	int x, y;

	for (y = 0; y < y0; y++) {
		for (x = 0; x < width[n]; x++) {
			if (image[n][x][y] <= thvalueDark)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
	for (y = y1; y < height[n]; y++) {
		for (x = 0; x < width[n]; x++) {
			if (image[n][x][y] <= thvalueDark)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
	for (y = y0; y < y1; y++) {
		for (x = 0; x < x0; x++) {
			if (image[n][x][y] <= thvalueDark)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
	for (y = y0; y < y1; y++) {
		for (x = x1; x < width[n]; x++) {
			if (image[n][x][y] <= thvalueDark)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
	for (y = y0; y < y1; y++) {
		for (x = x0; x < x1; x++) {
			if (image[n][x][y] <= thvalueBright)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
}


void normalBinarize(int n) {
	int thvalueDark = 130;
	int x, y;
	for (y = 0; y < height[n]; y++) {
		for (x = 0; x < width[n]; x++) {
			if (image[n][x][y] <= thvalueDark)image[n][x][y] = 0;
			else image[n][x][y] = 255;
		}
	}
}