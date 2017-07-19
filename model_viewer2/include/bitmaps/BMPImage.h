#ifndef BMP_IMAGE_HPP
	#define BMP_IMAGE_HPP
	
	#include <bitmaps/Bitmap.h>
	
	#include <string>
	#include <vector>
	#include <fstream>
	
	#define BITMAP_SIGNATURE 0x4d42
	#define BITMAP_HEADER_SIZE sizeof(uint16_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t)
	
	#define BITMAP_NO_COMPRESSION 0x0000
	#define BITMAP_NO_RLE_8_BITS 0x0001
	#define BITMAP_NO_COMPRESSION 0x0002
	#define BITMAP_NO_COMPRESSION 0x0003
	
	namespace GEngine
	{
		class BMPImage : public Bitmap
		{
			private:
				uint32_t m_nb_color_palette;
				std::vector<uint32_t> m_color_palette;
				uint32_t m_compression;
				uint16_t m_bit_count;
			
				bool readFileHeader(std::ifstream *fd);
				bool readImageHeader(std::ifstream *fd);
				bool readPalette(std::ifstream *fd);
				bool readImageData(std::ifstream *fd);
				
				bool readUnCompressedData();
				
			public:
				BMPImage(std::string filename);
				
				void loadFile(std::string filename);
		};
	}
	
	
#endif
