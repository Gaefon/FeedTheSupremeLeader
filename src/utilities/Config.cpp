#include <iostream>
#include <utilities/Config.h>

Config *Config::m_instance = NULL;

Config::Config()
{
	m_fullscreen = false;
}

Config *Config::getInstance()
{
	if (m_instance == NULL)
		m_instance = new Config();
	return m_instance;
}

bool Config::getFullscreen()
{
	return m_fullscreen;
}

void Config::setFullscreen(bool value)
{
	m_fullscreen = value;
}