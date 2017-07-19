#include <iostream>

#include <bitmaps/BMPImage.h>

using namespace std;

namespace GEngine
{
	BMPImage::BMPImage(string filename) : Bitmap()
	{
		loadFile(filename);
	}
	
	void BMPImage::loadFile(string filename)
	{
		ifstream fd;
		
		fd.open(filename, ios::binary);
		
		if (fd.is_open())
		{
			bool is_ok;
			// read the header
			is_ok = readFileHeader(&fd);
			
			if (is_ok)
				is_ok = readImageHeader(&fd);
			
			if (is_ok)
				is_ok = readPalette(&fd);
			
			if (is_ok)
				is_ok = readImageData(&fd);
			
			fd.close();
		}
		else
			cerr << "BMP Image : error opening file" << endl;
	}
	
	bool BMPImage::readFileHeader(ifstream *fd)
	{
		uint16_t signature;
		uint32_t size;
		uint32_t reserved;
		uint32_t offset;
		
		fd->read((char*) &signature, sizeof(signature));
		fd->read((char*) &size, sizeof(size));
		fd->read((char*) &reserved, sizeof(reserved));
		fd->read((char*) &offset, sizeof(offset));
		
		cout  << "====== HEADER ======" << endl;
		cout << "signature : " << hex << signature << endl;
		cout << "size : " << dec << size << endl;
		cout << "reserved : " << hex << reserved << endl;
		cout << "offset : " << hex << offset << endl;
		
		if (signature != BITMAP_SIGNATURE)
			return false;
		
		return true;
	}
	
	bool BMPImage::readImageHeader(ifstream *fd)
	{
		uint32_t header_size;
		int32_t width;
		int32_t height;
		uint16_t planes; // always 1
		uint32_t size_image;
		int32_t pix_per_meter_x;
		int32_t pix_per_meter_y;
		uint32_t nb_important_color;
		
		/*uint32_t RedMask;
		uint32_t GreenMask;
		uint32_t BlueMask;
		uint32_t AlphaMask;
		uint32_t CsType;
		uint32_t Endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
		uint32_t GammaRed;
		uint32_t GammaGreen;
		uint32_t GammaBlue;*/
		
		fd->read((char*) &header_size, sizeof(header_size));
		fd->read((char*) &width, sizeof(width));
		fd->read((char*) &height, sizeof(height));
		fd->read((char*) &planes, sizeof(planes)); // equals to 1
		fd->read((char*) &m_bit_count, sizeof(m_bit_count));
		fd->read((char*) &m_compression, sizeof(m_compression)); // 0 -> no compression, 1 -> RLE 8bits, 2 -> RLE 4bits, 3 -> bitmask
		fd->read((char*) &size_image, sizeof(size_image));
		fd->read((char*) &pix_per_meter_x, sizeof(pix_per_meter_x));
		fd->read((char*) &pix_per_meter_y, sizeof(pix_per_meter_y));
		fd->read((char*) &m_nb_color_palette, sizeof(m_nb_color_palette));
		fd->read((char*) &nb_important_color, sizeof(nb_important_color));
		
		cout  << "====== HEADER ======" << endl;
		cout << "header_size : " << hex << header_size << endl;
		cout << "width : " << dec << width << endl;
		cout << "height : " << dec << height << endl;
		cout << "planes : " << dec << planes << endl;
		cout << "bit_count : " << dec << m_bit_count << endl;
		cout << "compression : " << hex << m_compression << endl;
		
		
		cout << "size_image : " << hex << size_image << endl;
		cout << "pix_per_meter_x : " << hex << pix_per_meter_x << endl;
		cout << "pix_per_meter_y : " << hex << pix_per_meter_y << endl;
		cout << "m_nb_color_palette : " << hex << m_nb_color_palette << endl;
		cout << "nb_important_color : " << hex << nb_important_color << endl;
		
		
		fd->seekg(BITMAP_HEADER_SIZE + header_size, std::ios::beg);
		
		setSize(width, height);
		
		return true;
	}
	
	bool BMPImage::readPalette(ifstream *fd)
	{
		uint32_t rgba;
		
		// read all the colors.
		for (uint32_t i = 0; i < m_nb_color_palette; i++)
		{
			fd->read((char *) &rgba, sizeof(uint32_t));
			m_color_palette.push_back(rgba);
		}
		
		return true;
	}
	
	bool BMPImage::readImageData(ifstream *fd)
	{
		if (m_compression == 0)
			return readUnCompressedData();
		return false;
	}
	
	
	bool BMPImage::readUnCompressedData()
	{
		return false;
	}
	
}
