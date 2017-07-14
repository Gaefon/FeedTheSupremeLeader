#ifndef BITMAP_H
#define BITMAP_H

namespace GEngine
{
	class Bitmap
	{
		private:
			unsigned int width;
			unsigned int height;
			int  **data;
		public:
			Bitmap();
			~Bitmap();
	};
}

#endif
