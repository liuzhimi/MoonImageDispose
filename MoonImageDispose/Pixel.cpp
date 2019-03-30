#include "pch.h"
#include "pixel.h"

Pixel::Pixel()
{
	width = 0;
	height = 0;
	pixel = NULL;
}

Pixel::Pixel(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixel = (PixelRGBA*)malloc(sizeof(PixelRGBA)*width*height);
}

Pixel::~Pixel()
{
	if (pixel)
		free(pixel);
	pixel = NULL;
	width = 0;
	height = 0;
}

void Pixel::SetSize(unsigned int width, unsigned int height)
{
	if (width && height)
	{
		if (pixel)
			free(pixel);
		this->width = width;
		this->height = height;
		pixel = (PixelRGBA*)malloc(sizeof(PixelRGBA)*width*height);
	}
}


unsigned int Pixel::Width()
{
	return width;
}
unsigned int Pixel::Height()
{
	return height;
}

PixelRGBA& Pixel::operator[](int i)
{
	return pixel[i];
}

PixelRGBA& Pixel::At(int x, int y)
{
	return pixel[y*width + x];
}