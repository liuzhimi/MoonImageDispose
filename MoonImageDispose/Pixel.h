#pragma once
#include "pch.h";
#include<Windows.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct PixelRGBA {
	BYTE b;
	BYTE g;
	BYTE r;
	BYTE a;
}PixelRGBA;

class Pixel {
private:
	unsigned int width;
	unsigned int height;
	PixelRGBA *pixel;

public:
	Pixel();
	Pixel(unsigned int width, unsigned int height);
	~Pixel();
	void SetSize(unsigned int width, unsigned int height);//设置尺寸会清除所有图像数据
	unsigned int Width();
	unsigned int Height();
	PixelRGBA& operator[](int i);
	PixelRGBA& At(int i, int j);

};