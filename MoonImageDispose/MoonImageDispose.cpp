#include "pch.h";
#include "MoonBitmap.h"
#include "BitmapUtil.h"
#include <iostream>

int main()
{
	Pixel src, p1, p2, p3;
	MoonBitmap bmp;

	bmp.LoadBitMap("000018.BMP", &src);

	/*BitmapUtil::MakeRedChannel(&src, &p1);
	bmp.SaveBitMap("./out/Red.bmp", &p1);

	BitmapUtil::MakeGreenChannel(&src, &p1);
	bmp.SaveBitMap("./out/Green.bmp", &p1);

	BitmapUtil::MakeBlueChannel(&src, &p1);
	bmp.SaveBitMap("./out/Blue.bmp", &p1);

	BitmapUtil::MakeGray(&src, &p1);
	bmp.SaveBitMap("./out/Gray.bmp", &p1);

	BitmapUtil::MakeAverage(&p1, &p2);
	bmp.SaveBitMap("./out/Average.bmp", &p2);

	BitmapUtil::MakeHistogram(&p2, &p3);
	bmp.SaveBitMap("./out/AverageHistogram.bmp", &p3);

	BitmapUtil::MakeHistogram(&p1, &p3);
	bmp.SaveBitMap("./out/Histogram.bmp", &p3);

	BitmapUtil::MakeAntiColor(&p1, &p2);
	bmp.SaveBitMap("./out/AntiGray.bmp", &p2);

	BitmapUtil::MakeAntiColor(&src, &p2);
	bmp.SaveBitMap("./out/AntiOrigin.bmp", &p2);

	BitmapUtil::MakeAntiColor(&p2, &p1);
	bmp.SaveBitMap("./out/AntiAntiOrigin.bmp", &p1);

	BitmapUtil::MakeMeanFilter(&src, &p1);
	bmp.SaveBitMap("./out/MeanFilter.bmp", &p1);

	BitmapUtil::MakeMedianFilter(&src, &p1);
	bmp.SaveBitMap("./out/MedianFilter.bmp", &p1);
	
	BitmapUtil::MakeScalePic(&src, &p1, 10);
	bmp.SaveBitMap("./out/ScalePic.bmp", &p1);

	BitmapUtil::MakeScalePic(&src, &p2, 0.5);
	bmp.SaveBitMap("./out/ScalePic1.bmp", &p2);

	BitmapUtil::MakeTranslation(&src, &p1, &p2, -20, -30);
	bmp.SaveBitMap("./out/Translation.bmp", &p2);

	BitmapUtil::MakeMirror(&src, &p1);
	bmp.SaveBitMap("./out/Mirror.bmp", &p1);

	BitmapUtil::MakeRotate(&src, &p1, 45.0);
	bmp.SaveBitMap("./out/Rotate.bmp", &p1);*/

	BitmapUtil::MakeGray(&src, &p1);
	bmp.SaveBitMap("./out/Gray.bmp", &p1);

	BitmapUtil::MakeSegmentationWithFixedNum(&p1, &p2, 100);
	bmp.SaveBitMap("./out/Segment/Fixed.bmp", &p2);

	BitmapUtil::MakeSegmentationWithIterativeThresholdMethod(&p1, &p2);
	bmp.SaveBitMap("./out/Segment/Iterative.bmp", &p2);

	BitmapUtil::MakeSegmentationWithOstu(&p1, &p2);
	bmp.SaveBitMap("./out/Segment/Ostu.bmp", &p2);

	system("pause");
	return 0;
}

