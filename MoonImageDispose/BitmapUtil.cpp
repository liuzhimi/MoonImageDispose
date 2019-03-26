#include "pch.h";
#include "BitmapUtil.h";

int BitmapUtil::flag = 1;

void BitmapUtil::MakeRedChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i < len; i++)
	{
		(*dst)[i].r = (*src)[i].r;
		(*dst)[i].g = 0;
		(*dst)[i].b = 0;
		(*dst)[i].a = 0;
	}
}

void BitmapUtil::MakeGreenChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i < len; i++)
	{
		(*dst)[i].r = 0;
		(*dst)[i].g = (*src)[i].g;
		(*dst)[i].b = 0;
		(*dst)[i].a = 0;
	}
}

void BitmapUtil::MakeBlueChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i < len; i++)
	{
		(*dst)[i].r = 0;
		(*dst)[i].g = 0;
		(*dst)[i].b = (*src)[i].b;
		(*dst)[i].a = 0;
	}
}

void BitmapUtil::MakeGray(Pixel* src, Pixel* dst)
{
	unsigned int i, pix;
	unsigned int len = src->Width() * src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i < len; i++)
	{
		//pix = pixel[i*width+j].r*0.299+pixel[i*width+j].g*0.587+pixel[i*width+j].b*0.114;
		pix = (*src)[i].r * 306 + (*src)[i].g * 601 + (*src)[i].b * 117;
		//pix = pix / 1024;
		pix = pix >> 10;
		(*dst)[i].r = pix;
		(*dst)[i].g = pix;
		(*dst)[i].b = pix;
		(*dst)[i].a = 0;
	}
}

void BitmapUtil::MakeAntiColor(Pixel* src, Pixel* dst)
{
	unsigned int i, pix;
	unsigned int len = src->Width() * src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i < len; i++)
	{
		(*dst)[i].r = 255 - (*src)[i].r;
		(*dst)[i].g = 255 - (*src)[i].g;
		(*dst)[i].b = 255 - (*src)[i].b;
		(*dst)[i].a = 0;
	}
}

void BitmapUtil::MakeHistogram(Pixel* src, Pixel* dst)
{
	unsigned int len = src->Width() * src->Height();
	int grayTable[256] = {0};
	for (int i = 0; i < len; i++) {
		grayTable[(*src)[i].r]++;
	}
	dst->SetSize(256, 100);
	int maxPosition;
	int max = grayTable[0];
	for (int i = 0; i < 256; i++)
	{
		for (int j = i + 1; j < 256; j++)
		{
			if (max < grayTable[j]) {
				maxPosition = j;
				max = grayTable[j];
			}

		}
	}
	
	for (int i = 0; i < 256; i++)
	{
		grayTable[i] = 100 * grayTable[i] / max;
	}
	for (int i = 0; i < 256*100; i++)
	{
		(*dst)[i].r = 255;
		(*dst)[i].g = 255;
		(*dst)[i].b = 255;
		(*dst)[i].a = 0;
	}
	for (int i = 0; i < 256; i++)
	{
		int position = i + 256 * 99;
		for (int j = 0; j < grayTable[i]; j++)
		{
			(*dst)[position].r = 0;
			(*dst)[position].g = 0;
			(*dst)[position].b = 0;
			(*dst)[position].a = 0;
			position = position - 256;
		}
	}

}

void BitmapUtil::MakeAverage(Pixel* src, Pixel* dst)
{
	unsigned int len = src->Width() * src->Height();
	dst->SetSize(src->Width(), src->Height());
	int grayTable[256] = { 0 };
	int val = 0;
	for (int i = 0; i < len; i++) {
		grayTable[(*src)[i].r]++;
	}

	for (int i = 0; i < 256; i++) {
		val += grayTable[i];
		grayTable[i] = val * 255 / len;
	}

	for (int i = 0; i < len; i++)
	{
		(*dst)[i].r = grayTable[(*src)[i].r];
		(*dst)[i].g = grayTable[(*src)[i].r];
		(*dst)[i].b = grayTable[(*src)[i].r];
		(*dst)[i].a = 0;
	}

}

void BitmapUtil::MakeMeanFilter(Pixel* src, Pixel* dst)
{
	int width = src->Width();
	int height = src->Height();
	dst->SetSize(width, height);
	int x, y;
	for (y = 1; y < height - 1; y++) {
		for (x = 1; x < width - 1; x++) {
			dst->At(x, y).r = (src->At(x - 1, y - 1).r + src->At(x, y - 1).r + src->At(x + 1, y - 1).r + src->At(x - 1, y).r + src->At(x, y).r + src->At(x + 1, y).r + src->At(x - 1, y + 1).r + src->At(x, y + 1).r + src->At(x + 1, y + 1).r)/ 9;
			dst->At(x, y).b = (src->At(x - 1, y - 1).b + src->At(x, y - 1).b + src->At(x + 1, y - 1).b + src->At(x - 1, y).b + src->At(x, y).b + src->At(x + 1, y).b + src->At(x - 1, y + 1).b + src->At(x, y + 1).b + src->At(x + 1, y + 1).b) / 9;
			dst->At(x, y).g = (src->At(x - 1, y - 1).g + src->At(x, y - 1).g + src->At(x + 1, y - 1).g + src->At(x - 1, y).g + src->At(x, y).g + src->At(x + 1, y).g + src->At(x - 1, y + 1).g + src->At(x, y + 1).g + src->At(x + 1, y + 1).g) / 9;
			dst->At(x, y).a = 0;
		}
	}

	for (x = 0; x < width; x++)
	{
		dst->At(x, 0).r = src->At(x, 0).r;
		dst->At(x, 0).g = src->At(x, 0).g;
		dst->At(x, 0).b = src->At(x, 0).b;
		dst->At(x, 0).a = src->At(x, 0).a;
		dst->At(x, height - 1).r = src->At(x, height - 1).r;
		dst->At(x, height - 1).g = src->At(x, height - 1).g;
		dst->At(x, height - 1).b = src->At(x, height - 1).b;
		dst->At(x, height - 1).a = src->At(x, height - 1).a;
	}

	for (y = 0; y < height; y++)
	{
		dst->At(0, y).r = src->At(0, y).r;
		dst->At(0, y).g = src->At(0, y).g;
		dst->At(0, y).b = src->At(0, y).b;
		dst->At(0, y).a = src->At(0, y).a;
		dst->At(width - 1, y).r = src->At(width - 1, y).r;
		dst->At(width - 1, y).g = src->At(width - 1, y).g;
		dst->At(width - 1, y).b = src->At(width - 1, y).b;
		dst->At(width - 1, y).a = src->At(width - 1, y).a;
	}
}

void BitmapUtil::MakeMedianFilter(Pixel* src, Pixel* dst) {
	int width = src->Width();
	int height = src->Height();
	dst->SetSize(width, height);
	int x, y;
	for (y = 1; y < height - 1; y++) {
		for (x = 1; x < width - 1; x++) {
			dst->At(x, y).r = FindMid(src, x, y);
			dst->At(x, y).g = FindMid(src, x, y);
			dst->At(x, y).b = FindMid(src, x, y);
			dst->At(x, y).a = 0;
		}
	}

	for (x = 0; x < width; x++)
	{
		dst->At(x, 0).r = src->At(x, 0).r;
		dst->At(x, 0).g = src->At(x, 0).g;
		dst->At(x, 0).b = src->At(x, 0).b;
		dst->At(x, 0).a = src->At(x, 0).a;
		dst->At(x, height - 1).r = src->At(x, height - 1).r;
		dst->At(x, height - 1).g = src->At(x, height - 1).g;
		dst->At(x, height - 1).b = src->At(x, height - 1).b;
		dst->At(x, height - 1).a = src->At(x, height - 1).a;
	}

	for (y = 0; y < height; y++)
	{
		dst->At(0, y).r = src->At(0, y).r;
		dst->At(0, y).g = src->At(0, y).g;
		dst->At(0, y).b = src->At(0, y).b;
		dst->At(0, y).a = src->At(0, y).a;
		dst->At(width - 1, y).r = src->At(width - 1, y).r;
		dst->At(width - 1, y).g = src->At(width - 1, y).g;
		dst->At(width - 1, y).b = src->At(width - 1, y).b;
		dst->At(width - 1, y).a = src->At(width - 1, y).a;
	}
}

int BitmapUtil::FindMid(Pixel* src, int x, int y) {
	if (BitmapUtil::flag == 1) {

		BitmapUtil::flag = 2;
		return CountMid(src->At(x, y).r, src->At(x - 1, y).r, src->At(x + 1, y).r, src->At(x, y - 1).r, src->At(x, y + 1).r, src->At(x - 1, y - 1).r, src->At(x + 1, y + 1).r, src->At(x - 1, y + 1).r, src->At(x + 1, y - 1).r);
	}
	else if (BitmapUtil::flag == 2) {
		BitmapUtil::flag = 3;
		return CountMid(src->At(x, y).g, src->At(x - 1, y).g, src->At(x + 1, y).g, src->At(x, y - 1).g, src->At(x, y + 1).g, src->At(x - 1, y - 1).g, src->At(x + 1, y + 1).g, src->At(x - 1, y + 1).g, src->At(x + 1, y - 1).g);
	}
	else {
		BitmapUtil::flag = 1;
		return CountMid(src->At(x, y).b, src->At(x - 1, y).b, src->At(x + 1, y).b, src->At(x, y - 1).b, src->At(x, y + 1).b, src->At(x - 1, y - 1).b, src->At(x + 1, y + 1).b, src->At(x - 1, y + 1).b, src->At(x + 1, y - 1).b);
	}
}

int BitmapUtil::CountMid(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9) {
	int array[9] = { x1, x2, x3, x4, x5, x6, x7, x8, x9 };
	for (int i = 0; i < 9; i++) {
		int minIndex = i;
		for (int j = i; j < 9; j++) {

			if (array[minIndex] > array[j])
			{
				minIndex = j;
			}
		}
		int temp = array[0];
		array[0] = array[minIndex];
		array[minIndex] = temp;
	}
	return array[5];
}