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
	void SetSize(unsigned int width, unsigned int height);//���óߴ���������ͼ������
	unsigned int Width();
	unsigned int Height();
	PixelRGBA& operator[](int i);
	PixelRGBA& At(int i, int j);

};