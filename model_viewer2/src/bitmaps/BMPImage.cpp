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
		uint32_t reserved;
		
		fd->read((char*) &signature, sizeof(signature));
		fd->read((char*) &m_size, sizeof(m_size));
		fd->read((char*) &reserved, sizeof(reserved));
		fd->read((char*) &m_offset, sizeof(m_offset));
		
		/*cout  << "====== HEADER ======" << endl;
		cout << "signature : " << hex << signature << endl;
		cout << "size : " << dec << m_size << endl;
		cout << "reserved : " << hex << reserved << endl;
		cout << "offset : " << dec << m_offset << endl;*/
		
		if (signature != BITMAP_SIGNATURE)
		{
			cerr << "BMP Image : bad signature" << endl;
			return false;
		}
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
		
		/*cout  << "====== HEADER ======" << endl;
		cout << "header_size : " << hex << header_size << endl;
		cout << "width : " << dec << width << endl;
		cout << "height : " << dec << height << endl;
		cout << "planes : " << dec << planes << endl;
		cout << "bit_count : " << dec << m_bit_count << endl;
		cout << "compression : " << hex << m_compression << endl;
		
		
		cout << "size_image : " << hex << size_image << endl;
		cout << "pix_per_meter_x : " << dec << pix_per_meter_x << endl;
		cout << "pix_per_meter_y : " << dec << pix_per_meter_y << endl;
		cout << "m_nb_color_palette : " << dec << m_nb_color_palette << endl;
		cout << "nb_important_color : " << dec << nb_important_color << endl;*/
		
		
		fd->seekg(BITMAP_HEADER_SIZE + header_size, std::ios::beg);
		
		setSize(width, height);
		
		return true;
	}
	
	bool BMPImage::readPalette(ifstream *fd)
	{
		uint32_t rgba;
		
		m_color_palette.clear();
		
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
		bool read_success = false;
		fd->seekg(m_offset, std::ios::beg);
		m_image_data.clear(); // clear all the data
		
		if (m_compression == 0)
			read_success = readUnCompressedData(fd);
		else if (m_compression == BITMAP_RLE_8_BITS)
			read_success = readRle8BitsData(fd);
		else if (m_compression == BITMAP_RLE_4_BITS)
			read_success = readRle4BitsData(fd);
		else if (m_compression == BITMAP_BITMASK)
			read_success = readBitmaskData(fd);
			
		if (read_success)
		{
			if (m_bit_count == 24)
				return decode24BitsData();
			else if (m_bit_count == 16)
				return decode16BitsData();
			return false;
		}
		return false;
	}
	
	
	bool BMPImage::readUnCompressedData(ifstream *fd)
	{
		// 4 * 4 * 24bits = 48 octets
		// size - offset = 48 octets
		// WARNING : if line size is not a multiple of 4 then adds bytes to make a multiple of 4
		int data_size = m_size - m_offset;
		uint8_t byte;
		int bytes_to_jump = 0;
		
		if (getWidth() % 4 != 0)
			bytes_to_jump = 4 - ((getWidth() * m_bit_count / 8) % 4);
			
		int real_size_to_read = data_size - (getHeight() * bytes_to_jump);
		
		for (int i = 0; i < real_size_to_read; i++)
		{
			if (i != 0 && i % (getWidth() * m_bit_count / 8) == 0)
				fd->seekg(bytes_to_jump, ios::cur);
			
			fd->read((char *) &byte, sizeof(uint8_t));
			m_image_data.push_back(byte);
		}
		
		return true;
	}
	
	bool BMPImage::readRle8BitsData(ifstream *fd)
	{
		cerr << "RLE 8 bits compression is not supported :(" << endl;
		return false;
	}
	
	bool BMPImage::readRle4BitsData(ifstream *fd)
	{
		cerr << "RLE 4 bits compression is not supported :(" << endl;
		return false;
	}
	
	bool BMPImage::readBitmaskData(ifstream *fd)
	{
		cerr << "bitmask compression is not supported :(" << endl;
		return false;
	}
	
	bool BMPImage::decode24BitsData()
	{
		int nb_pix = getWidth() * getHeight();
		int nb_pix_read = m_image_data.size() / (24 / 8);
		int pix_color;
		int r, g, b;
		
		if (nb_pix == nb_pix_read)
		{
			for (int i = 0; i < nb_pix; i++)
			{
				pix_color = 0xff000000;
				// little endian
				b = m_image_data.at(3 * i);
				g = m_image_data.at(3 * i + 1);
				r = m_image_data.at(3 * i + 2);
				
				pix_color |= (b << 16) | (g << 8) | r;
				//cout << hex << pix_color << endl;
				
				// start from the bottom
				setPixel(i % getWidth(), getHeight() - i / getHeight() - 1, pix_color);
			}
			
			return true;
		}
		else
			cerr << "BMP image : wrong number of pixel read" << endl;
		
		return false;
	}
	
	bool BMPImage::decode16BitsData()
	{
		/*int nb_pix = getWidth() * getHeight();
		int nb_pix_read = m_image_data.size() / (16 / 8);
		int pix_color;
		int r, g, b;
		
		if (nb_pix == nb_pix_read)
		{}
		else
			cerr << "BMP image : wrong number of pixel read" << endl;*/
		
		return false;
	}
	
}
