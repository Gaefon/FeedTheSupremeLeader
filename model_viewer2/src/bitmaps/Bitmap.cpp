#include <bitmaps/Bitmap.h>
#include <iostream>

using namespace std;

namespace GEngine
{
	Bitmap::Bitmap()
	{
		width = 0;
		height = 0;
		data = nullptr;
	}
	
	Bitmap::~Bitmap()
	{
		deallocateData();
	}
	
	void Bitmap::deallocateData()
	{
		if (data != nullptr)
		{
			/*for (unsigned int i = 0; i < width; i++)
				delete[] data[i];*/
			delete[] data;
			data = nullptr;
		}
	}
	
	void Bitmap::setSize(unsigned int w, unsigned int h)
	{
		deallocateData();
	
		width = w;
		height = h;
		
		data = new unsigned int[width * height];
		
		for (unsigned int i = 0; i < width * height; i++)
			data[i] = 0x00000000;
	}
	
	void Bitmap::setPixel(unsigned int x, unsigned int y, unsigned int value)
	{
		if (x < width && y < width)
			data[y * width + x] = value;
		else
			cerr << "Bitmap :: wrong pixel position (x : " << x << ", y : " << y << ")" << endl;
	}
	
	unsigned int *Bitmap::getPixels()
	{
		return data;
	}
	
	
	unsigned int Bitmap::getWidth()
	{
		return width;
	}
	
	unsigned int Bitmap::getHeight()
	{
		return height;
	}
}
