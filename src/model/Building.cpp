#include <model/Building.hpp>

Building::Building()
{
	//ctor
}

unsigned int Building::getWidth()
{
	return m_width;
}

void Building::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int Building::getHeight()
{
	return m_height;
}

void Building::setHeight(unsigned int val)
{
	m_height = val;
}

Building::~Building()
{
	//dtor
}
