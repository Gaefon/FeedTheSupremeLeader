#ifndef BITMAP_H
	#define BITMAP_H

	namespace GEngine
	{
		class Bitmap
		{
			private:
				unsigned int width;
				unsigned int height;
				
				unsigned int **data; // all the colors ar coded in R8G8B8A8
			
				void deallocateData();
			public:
				Bitmap();
				~Bitmap();
				void setSize(unsigned int w, unsigned int h);
				void setPixel(unsigned int x, unsigned int y, unsigned int value);
				unsigned int **getPixels();
		};
	}

#endif
