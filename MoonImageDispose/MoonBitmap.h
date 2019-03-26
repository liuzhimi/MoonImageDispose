#pragma once
#include "pixel.h"


class MoonBitmap {
public:
	Pixel* pixel;
private:
	FILE* fp;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	unsigned int QUADlenth;
	unsigned width;
	unsigned height;

public:
	MoonBitmap();
	//载入位图
	void LoadBitMap(const char *file, Pixel* pixel);
	//保存为24位位图
	void SaveBitMap(const char *file, Pixel* pixel);


	~MoonBitmap();

private:
	void LoadBI_RGB();

	void LoadTRUE_COLOR(BYTE* row, UINT lenth, UINT col);
};