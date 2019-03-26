#pragma once
#include "Pixel.h"

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

private:
	static int FindMid(Pixel* src, int x, int y);
	static int CountMid(int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9);

public:
	static int flag;
};