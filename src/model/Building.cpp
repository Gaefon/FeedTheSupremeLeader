#include "Building.hpp"

Building::Building()
{
	//ctor
}

unsigned int getWidth()
{
	return m_width;
}

void setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int getHeight()
{
	return m_height;
}

void setHeight(unsigned int val)
{
	m_height = val;
}

Building::~Building()
{
	//dtor
}
