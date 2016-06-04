#include <iostream>
#include <utilities/Config.h>

Config::Config()
{
	m_fullscreen = false;
}

bool Config::get(Config::Variable var)
{
	if (var == Fullscreen)
		return m_fullscreen;
	return false;
}

void Config::set(Config::Variable var, bool value)
{
	if (var == Fullscreen)
		m_fullscreen = value;
}