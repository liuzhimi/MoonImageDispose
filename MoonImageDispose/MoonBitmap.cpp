#include "pch.h";
#include "MoonBitmap.h"
#pragma warning(disable:4996)

MoonBitmap::MoonBitmap() 
{

}

MoonBitmap::~MoonBitmap()
{

}

void MoonBitmap::LoadBitMap(const char *file, Pixel* pixel) 
{
	if (pixel==NULL)
	{
		return;
	}
	this->pixel = pixel;
	fp = fopen(file, "rb");
	if (fp == NULL)
	{
		return;
	}
	fread(&fileheader.bfType, sizeof(WORD), 1, fp);
	fread(&fileheader.bfSize, sizeof(DWORD), 1, fp);
	fread(&fileheader.bfReserved1, sizeof(WORD), 1, fp);
	fread(&fileheader.bfReserved2, sizeof(WORD), 1, fp);
	fread(&fileheader.bfOffBits, sizeof(DWORD), 1, fp);

	//根据文件头判断是否是bmp格式
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		this->pixel = NULL;
		return;
	}

	fread(&infoheader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = infoheader.biWidth;
	height = infoheader.biHeight;
	if (infoheader.biBitCount == 24)
	{
		QUADlenth = 0;
	}

	LoadBI_RGB();

	fclose(fp);
	this->pixel = NULL;
}

void MoonBitmap::LoadBI_RGB() 
{
	unsigned int i;

	BYTE* row;
	unsigned long stdWidth;

	if (infoheader.biBitCount == 24)
	{
		stdWidth = width * 3;
		i = stdWidth % 4;
		if (i > 0)
			stdWidth = stdWidth + 4 - i;
	}

	row = (BYTE*)malloc(sizeof(BYTE)*stdWidth);

	pixel->SetSize(width, height);

	fseek(fp, fileheader.bfOffBits, SEEK_SET);

	for (i = 0; i < height && !feof(fp); i++)
	{
		//cout<<"loading line "<<height-i-1<<"... ";
		fread(row, sizeof(BYTE)*stdWidth, 1, fp);

		if (infoheader.biBitCount == 24)
			LoadTRUE_COLOR(row, width * 3, height - i - 1);
	}
	free(row);
}

void MoonBitmap::LoadTRUE_COLOR(BYTE* row, UINT lenth, UINT col)
{
	unsigned int i = 0, j = 0, line = 0;
	line = col * width;
	for (i = 0; i < lenth; i = i + 3)
	{
		(*pixel)[line + j].b = row[i];
		(*pixel)[line + j].g = row[i + 1];
		(*pixel)[line + j].r = row[i + 2];
		(*pixel)[line + j].a = 0;

		j++;
	}
}

void MoonBitmap::SaveBitMap(const char *file, Pixel* pixel)
{
	unsigned long stdWidth;
	BYTE blank = 0;
	int i, j, k;
	BYTE *row;

	fp = fopen(file, "wb");
	if (fp == NULL)
		return;
	if (pixel == NULL)
		return;
	this->pixel = pixel;
	//设置尺寸
	width = pixel->Width();
	height = pixel->Height();
	if (width*height == 0)
		return;
	//计算每行的字节数
	stdWidth = width * 3;
	i = stdWidth % 4;
	if (i > 0)
		stdWidth = stdWidth + 4 - i;
	//生成文件头
	fileheader.bfType = 0x4D42;
	fileheader.bfSize = stdWidth * height + 54;
	fileheader.bfReserved1 = 0;
	fileheader.bfReserved2 = 0;
	fileheader.bfOffBits = 54;
	//生成位图信息头
	infoheader.biSize = 40;
	infoheader.biWidth = width;
	infoheader.biHeight = height;
	infoheader.biPlanes = 1;
	infoheader.biBitCount = 24;
	infoheader.biCompression = 0;
	infoheader.biSizeImage = stdWidth * height;
	infoheader.biXPelsPerMeter = 96;
	infoheader.biYPelsPerMeter = 96;
	infoheader.biClrUsed = 0;
	infoheader.biClrImportant = 0;
	//写入头部信息
	fwrite(&fileheader.bfType, sizeof(WORD), 1, fp);
	fwrite(&fileheader.bfSize, sizeof(DWORD), 1, fp);
	fwrite(&fileheader.bfReserved1, sizeof(WORD), 1, fp);
	fwrite(&fileheader.bfReserved2, sizeof(WORD), 1, fp);
	fwrite(&fileheader.bfOffBits, sizeof(DWORD), 1, fp);
	fwrite(&infoheader, sizeof(BITMAPINFOHEADER), 1, fp);

	//行缓存
	row = (BYTE*)malloc(sizeof(BYTE)*stdWidth);
	//从最后一行开始保存
	for (i = height - 1; i >= 0; i--)
	{
		k = 0;
		for (j = 0; j < width; j++)
		{
			row[k] = ((*pixel)[i*width + j].b);
			k++;
			row[k] = ((*pixel)[i*width + j].g);
			k++;
			row[k] = ((*pixel)[i*width + j].r);
			k++;
		}
		//j = j*3;
		//剩余部分填充0，凑齐4的倍数
		for (; k < stdWidth; k++)
		{
			row[k] = 0;
		}
		//写入一行
		fwrite(row, sizeof(BYTE)*stdWidth, 1, fp);
		//break;
	}
	free(row);
	fclose(fp);
	this->pixel = NULL;
}