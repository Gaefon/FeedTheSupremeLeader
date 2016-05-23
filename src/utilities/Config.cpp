#include <iostream>
#include <utilities/Config.h>

Config::Config()
{
	m_fullscreen = false;
}

bool Config::getFullscreen()
{
	return m_fullscreen;
}

void Config::setFullscreen(bool value)
{
	m_fullscreen = value;
}