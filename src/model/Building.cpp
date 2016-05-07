#include <iostream>
#include <model/Building.hpp>

using namespace std;

Building::Building()
{
	//ctor
}

void Building::setWidth(unsigned int val)
{
	m_width = val;
}

unsigned int Building::getWidth()
{
	return m_width;
}

void Building::setHeight(unsigned int val)
{
	m_height = val;
}

unsigned int Building::getHeight()
{
	return m_height;
}

string Building::getName()
{
	return m_name;
}

void Building::setName(string val)
{
	m_name = val;
}

Building::~Building()
{
	//dtor
}
