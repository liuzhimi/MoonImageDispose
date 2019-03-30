#pragma once
#include "Pixel.h"

#define PI 3.1415926

class BitmapUtil
{
public:
	static void MakeRedChannel(Pixel* src, Pixel* dst);
	static void MakeGreenChannel(Pixel* src, Pixel* dst);
	static void MakeBlueChannel(Pixel* src, Pixel* dst);
	static void MakeGray(Pixel* src, Pixel* dst);
	static void MakeAntiColor(Pixel* src, Pixel* dst);
	static void MakeHistogram(Pixel* src, Pixel* dst);
	static void MakeAverage(Pixel* src, Pixel* dst);//���⻯
	static void MakeMeanFilter(Pixel* src, Pixel* dst);//��ֵ�˲�
	static void MakeMedianFilter(Pixel* src, Pixel* dst);//��ָ�˲�
	static void MakeScalePic(Pixel* src, Pixel* dst, double inSampleSize);//˫���Բ�ֵ����ͼƬ
	static void MakeTranslation(Pixel* src, Pixel* temp, Pixel* dst, int x, int y);//ƽ��ͼƬ
	static void MakeMirror(Pixel* src, Pixel* dst);
	static void MakeRotate(Pixel* src, Pixel* dst, double degree);

private:
	static int FindMid(Pixel* src, int x, int y);
	static int CountMid(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9);
	static void MoveX(Pixel* src, Pixel* temp, Pixel* dst, int x, int y);
	static void MoveY(Pixel* src, Pixel* temp, Pixel* dst, int x, int y);

public:
	static int flag;
};