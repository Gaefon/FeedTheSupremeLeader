#include <iostream>
#include <model/Building.hpp>

using namespace std;

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
