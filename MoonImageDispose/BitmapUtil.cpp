#include "pch.h";
#include "BitmapUtil.h";
#include <cmath>

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

void BitmapUtil::MakeScalePic(Pixel* src, Pixel* dst, double inSampleSize)
{
	int dstWidth = src->Width() * inSampleSize;
	int dstHeight = src->Height() * inSampleSize;

	dst->SetSize(dstWidth, dstHeight);

	for (int i = 0; i < dstHeight; i++)
	{
		double srcY = i / inSampleSize;
		int intY = (int)srcY;
		double v = srcY - intY;
		double v1 = 1.0 - v;
		for (int j = 0; j < dstWidth; j++)
		{
			double srcX = j / inSampleSize;
			int intX = (int)srcX;
			double u = srcX - intX;
			double u1 = 1.0 - u;

			int indexLeftX = intX;
			int indexRightX;
			if (indexLeftX + 1 < src->Width())
			{
				indexRightX = indexLeftX + 1;
			}
			else 
			{
				indexRightX = indexLeftX;
			}
			int indexTopY = intY;
			int indexBelowY;
			if (indexTopY + 1 < src->Height())
			{
				indexBelowY = indexTopY + 1;
			}
			else 
			{
				indexBelowY = indexTopY;
			}
			dst->At(j, i).r = v1*(u*src->At(indexRightX, indexTopY).r + u1 * src->At(indexLeftX, indexTopY).r)
				+ v * (u * src->At(indexRightX, indexBelowY).r + u1 * src->At(indexLeftX, indexBelowY).r);
			dst->At(j, i).g = v1*(u*src->At(indexRightX, indexTopY).g + u1 * src->At(indexLeftX, indexTopY).g)
				+ v * (u * src->At(indexRightX, indexBelowY).g + u1 * src->At(indexLeftX, indexBelowY).g);
			dst->At(j, i).b = v1*(u*src->At(indexRightX, indexTopY).b + u1 * src->At(indexLeftX, indexTopY).b)
				+ v * (u * src->At(indexRightX, indexBelowY).b + u1 * src->At(indexLeftX, indexBelowY).b);
			dst->At(j, i).a = 0;
		}
	}
}

void BitmapUtil::MakeTranslation(Pixel* src, Pixel* temp, Pixel* dst, int x, int y)
{
	int width = src->Width();
	int height = src->Height();
	temp->SetSize(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			temp->At(i, j).a = 255;
			temp->At(i, j).r = 255;
			temp->At(i, j).g = 255;
			temp->At(i, j).b = 255;
		}
	}
	MoveX(src, temp, dst, x, y);
}

void BitmapUtil::MoveX(Pixel* src, Pixel* temp, Pixel* dst, int x, int y)
{
	int width = src->Width();
	int height = src->Height();
	if (x >= 0)
	{
		for (int i = 0; i + x < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				temp->At(i + x, j).a = src->At(i, j).a;
				temp->At(i + x, j).r = src->At(i, j).r;
				temp->At(i + x, j).g = src->At(i, j).g;
				temp->At(i + x, j).b = src->At(i, j).b;
			}
		}
		MoveY(src, temp, dst, x, y);
	}
	else {
		for (int i = width - 1; i + x > 0; i--)
		{
			for (int j = 0; j < height; j++)
			{
				temp->At(i + x, j).a = src->At(i, j).a;
				temp->At(i + x, j).r = src->At(i, j).r;
				temp->At(i + x, j).g = src->At(i, j).g;
				temp->At(i + x, j).b = src->At(i, j).b;
			}
		}
		MoveY(src,temp, dst, x, y);
	}
}

void BitmapUtil::MoveY(Pixel* src, Pixel* temp, Pixel* dst, int x, int y)
{
	int width = src->Width();
	int height = src->Height();
	dst->SetSize(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			dst->At(i, j).a = 255;
			dst->At(i, j).r = 255;
			dst->At(i, j).g = 255;
			dst->At(i, j).b = 255;
		}
	}
	if (y >= 0)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j  + y < height; j++)
			{
				dst->At(i, j + y).a = temp->At(i, j).a;
				dst->At(i, j + y).r = temp->At(i, j).r;
				dst->At(i, j + y).g = temp->At(i, j).g;
				dst->At(i, j + y).b = temp->At(i, j).b;
			}
		}
	}
	else {
		for (int i = 0; i < width; i++)
		{
			for (int j = height - 1; j + y > 0; j--)
			{
				dst->At(i, j + y).a = temp->At(i, j).a;
				dst->At(i, j + y).r = temp->At(i, j).r;
				dst->At(i, j + y).g = temp->At(i, j).g;
				dst->At(i, j + y).b = temp->At(i, j).b;
			}
		}
	}
}

void BitmapUtil::MakeMirror(Pixel* src, Pixel* dst)
{
	int width = src->Width();
	int height = src->Height();
	dst->SetSize(width, height);
	int x = 0;
	int y = 0;
	int dstX = 0;
	for (int i = 0; i < width; i++)
	{
		x = i;
		dstX = width - 1 - x;
		for (int j = 0; j < height; j++)
		{
			y = j;
			dst->At(x, y).a = src->At(dstX, y).a;
			dst->At(x, y).r = src->At(dstX, y).r;
			dst->At(x, y).g = src->At(dstX, y).g;
			dst->At(x, y).b = src->At(dstX, y).b;
		}
	}
}

void BitmapUtil::MakeRotate(Pixel* src, Pixel* dst, double degree)
{
	int widthSrc = src->Width();
	int heightSrc = src->Height();

	double radian = degree * PI / 180.0;
	double sinn = sin(radian);
	double coss = cos(radian);

	int widthDst = (int)(heightSrc * abs(sinn) + widthSrc * abs(coss));
	int heightDst = (int)(widthSrc * abs(sinn) + heightSrc * abs(coss));

	dst->SetSize(widthDst, heightDst);

	int dx = (int)(widthSrc / 2 * (1 - coss) + heightSrc / 2 * sinn);
	int dy = (int)(widthSrc / 2 * (0 - sinn) + heightSrc / 2 * (1 - coss));

	int insertBeginX = widthSrc / 2 - widthDst / 2;
	int insertBeginY = heightSrc / 2 - heightDst / 2;

	double ku = insertBeginX * coss - insertBeginY * sinn + dx;
	double kv = insertBeginX * sinn + insertBeginY * coss + dy;
	double cu1 = coss, cu2 = sinn;
	double cv1 = sinn, cv2 = coss;

	double fu, fv, a, b, F1, F2;
	int Iu, Iv;

	for (int i = 0; i < heightDst; i++) {
		for (int j = 0; j < widthDst; j++) {
			fu = j * cu1 - i * cu2 + ku;
			fv = j * cv1 + i * cv2 + kv;
			if ((fv) < 1 || (fv > heightSrc - 1) || (fu < 1) || (fu > widthSrc - 1))
			{
				dst->At(j, i).a = 0;
				dst->At(j, i).r = 150;
				dst->At(j, i).g = 150;
				dst->At(j, i).b = 150;
			}
			else
			{
				Iu = (int)fu;
				Iv = (int)fv;
				a = fu - Iu;
				b = fv - Iv;
				F1 = (1 - b)* (*src)[Iv * widthSrc + Iu].r + b * (*src)[(Iv + 1) * widthSrc + Iu].r;
				F2 = (1 - b)* (*src)[Iv * widthSrc + (Iu + 1)].r + b * (*src)[(Iv + 1) * widthSrc + (Iu + 1)].r;
				dst->At(j ,i).r = ((1 - a) * F1 + a * F2);
				//(*dst)[i * widthDst + j].r = ((1 - a) * F1 + a * F2);

				F1 = (1 - b)* (*src)[Iv * widthSrc + Iu ].g + b * (*src)[Iv * widthSrc + Iu ].g;
				F2 = (1 - b)* (*src)[Iv * widthSrc + (Iu + 1) ].g + b * (*src)[(Iv + 1) * widthSrc + (Iu + 1) ].g;
				dst->At(j, i).g = ((1 - a) * F1 + a * F2);
				//(*dst)[i * widthDst + j].g = ((1 - a) * F1 + a * F2);

				F1 = (1 - b)* (*src)[Iv * widthSrc + Iu ].b + b * (*src)[Iv * widthSrc + Iu ].b;
				F2 = (1 - b)* (*src)[Iv * widthSrc + (Iu + 1) ].b + b * (*src)[(Iv + 1) * widthSrc + (Iu + 1) ].b;
				dst->At(j, i).b = ((1 - a) * F1 + a * F2);
				//(*dst)[i * widthDst + j].b = ((1 - a) * F1 + a * F2);
			}
		}
		
	}
}

void BitmapUtil::MakeSegmentationWithFixedNum(Pixel* src, Pixel* dst, int num)
{
	int width = src->Width();
	int height = src->Height();
	dst->SetSize(width, height);

	for (int i = 0; i < width; i++)
	{

		for (int j = 0; j < height; j++)
		{
			if (src->At(i, j).r <= num)
			{
				dst->At(i, j).r = 0;
				dst->At(i, j).g = 0;
				dst->At(i, j).b = 0;
				dst->At(i, j).a = 0;
			}
			else {
				dst->At(i, j).r = 255;
				dst->At(i, j).g = 255;
				dst->At(i, j).b = 255;
				dst->At(i, j).a = 0;
			}
		}
	}
}

void BitmapUtil::MakeSegmentationWithIterativeThresholdMethod(Pixel* src, Pixel* dst)
{
	unsigned int len = src->Width() * src->Height();
	double grayTable[256] = { 0 };
	for (int i = 0; i < len; i++) {
		grayTable[(*src)[i].r]++;
	}
	int maxPosition;
	int max = 255;
	int min = 0;
	for (int i = 0; i < 256; i++)
	{
		for (int j = i + 1; j < 256; j++)
		{
			if (max < grayTable[j]) {
				max = j;
				continue;
			}

			if (min > grayTable[j])
			{
				min = j;
			}
		}
	}
	/*for (int i = 0; i < 256; i++)
	{
		grayTable[i] = grayTable[i] / len;
	}*/
	long threshold = (max + min) >> 1;
	int zo = 0, bo = 0;
	int sum1 = 0, sum2 = 0;
	long oldThreshold = threshold;
	long sum[256] = { 0 };
	long sumNum[256] = { 0 };
	sumNum[0] = grayTable[0];
	for (int i = 1; i < 256; i++) {
		sum[i] = sum[i - 1] + grayTable[i] * i;
		sumNum[i] = sumNum[i - 1] + grayTable[i];
	}
	do {
		if (sumNum[threshold] == 0)
		{
			zo = threshold;
		}
		else {
			zo = sum[threshold] / sumNum[threshold];
		}
		if ((sumNum[255] - sumNum[threshold])==0)
		{
			bo = threshold;
		}
		else {
			bo = (sum[255] - sum[threshold]) / (sumNum[255] - sumNum[threshold]);
		}
		
		oldThreshold = threshold;
		threshold = (zo + bo) >> 1;
	} while (oldThreshold != threshold);
	printf("%d\n", threshold);
	MakeSegmentationWithFixedNum(src, dst, threshold);
}

void BitmapUtil::MakeSegmentationWithOstu(Pixel* src, Pixel* dst)
{
	unsigned int len = src->Width() * src->Height();
	double hist[256] = { 0 };

	double omega[256];
	double mu[256];

	omega[0] = hist[0];
	mu[0] = 0;

	int threshold = 0;
	for (int i = 0; i < len; i++)
	{
		hist[(*src)[i].r]++;
	}
	for (int i = 0; i < 256; i++)
	{
		hist[i] = hist[i] / len;
	}
	for (int i = 1; i < 256; i++)
	{
		omega[i] = omega[i - 1] + hist[i]; //累积分布函数
		mu[i] = mu[i - 1] + i * hist[i];
	}
	double mean = mu[255];// 灰度平均值
	double max = 0;
	int k_max = 0;
	for (int k = 1; k < 255; k++)
	{
		double PA = omega[k]; // A类所占的比例
		double PB = 1 - omega[k]; //B类所占的比例
		double value = 0;
		if (fabs(PA) > 0.00 && fabs(PB) > 0.00)
		{
			double MA = mu[k] / PA; //A 类的灰度均值
			double MB = (mean - mu[k]) / PB;//B类灰度均值
			value = PA * (MA - mean) * (MA - mean) + PB * (MB - mean) * (MB - mean);//类间方差
			//printf("%f\n", value);
			if (value > max)
			{
				max = value;
				k_max = k;
			}
			//printf("%f\n", k);
		}
	}
	printf("%d\n", k_max);
	MakeSegmentationWithFixedNum(src, dst, k_max);
	
}