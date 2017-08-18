#ifndef BMP_IMAGE_HPP
	#define BMP_IMAGE_HPP
	
	#include <bitmaps/Bitmap.h>
	
	#include <string>
	#include <vector>
	#include <fstream>
	
	#define BITMAP_SIGNATURE 0x4d42
	#define BITMAP_HEADER_SIZE sizeof(uint16_t) + sizeof(uint32_t) + sizeof(uint32_t) + sizeof(uint32_t)
	
	#define BITMAP_NO_COMPRESSION 0x0000
	#define BITMAP_RLE_8_BITS 0x0001
	#define BITMAP_RLE_4_BITS 0x0002
	#define BITMAP_BITMASK 0x0003
	
	namespace GEngine
	{
		class BMPImage : public Bitmap
		{
			private:
			
				uint32_t m_size;
				uint32_t m_offset;
			
				uint32_t m_nb_color_palette;
				std::vector<uint32_t> m_color_palette;
				uint32_t m_compression;
				uint16_t m_bit_count;
				std::vector<uint8_t> m_image_data;
			
				bool readFileHeader(std::ifstream *fd);
				bool readImageHeader(std::ifstream *fd);
				bool readPalette(std::ifstream *fd);
				bool readImageData(std::ifstream *fd);
				
				bool readUnCompressedData(std::ifstream *fd);
				bool readRle8BitsData(std::ifstream *fd);
				bool readRle4BitsData(std::ifstream *fd);
				bool readBitmaskData(std::ifstream *fd);
				
				bool decode24BitsData();
				bool decode16BitsData();
				
			public:
				BMPImage(std::string filename);
				
				void loadFile(std::string filename);
		};
	}
	
	
#endif
