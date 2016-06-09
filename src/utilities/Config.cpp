#include <iostream>
#include <utilities/Config.h>
#include <utilities/sounds/sounds.h>
#include <Constants.hpp>

using namespace std;

Config::Config()
{
	m_fullscreen = false;
	m_music = true;
	m_map_sensivity = DEFAULT_MAP_SENSIVITY;
	m_audio_volume = 64;
}

bool Config::getBool(Config::Variable var)
{
	if (var == Fullscreen)
		return m_fullscreen;
	else if (var == Music)
		return m_music;
	return false;
}

int Config::getInt(Config::Variable var)
{
	if (var == MapSensivity)
		return m_map_sensivity;
	else if (var == AudioVolume)
		return m_audio_volume;
	return 0;
}

void Config::set(Config::Variable var, bool value)
{
	if (var == Fullscreen)
		m_fullscreen = value;
	else if (var == Music)
		m_music = value;
}

void Config::set(Config::Variable var, int value)
{
	if (var == MapSensivity)
		m_map_sensivity = value;
	if (var == AudioVolume) {
		Sounds::getInstance()->setMusicVolume(value);
		m_audio_volume = value;
	}
}

void Config::readConfiguration()
{
	ifstream config_file(CONFIG_FILE_NAME);
	Json::Value root;
	Json::Reader reader;

	bool parsing_successful = reader.parse(config_file, root, false);
	if (!parsing_successful)
		return;
	if (root["fullscreen"].isNull() == false)
		m_fullscreen = root["fullscreen"].asBool();
	if (root["music"].isNull() == false) {
		m_music = root["music"].asBool();
		if (m_music == false)
			Sounds::getInstance()->pauseMusic();
	}
	if (root["map_sensivity"].isNull() == false)
		m_map_sensivity = root["map_sensivity"].asInt();
	if (root["music_volume"].isNull() == false) {
			m_audio_volume = root["music_volume"].asInt();
			Sounds::getInstance()->setMusicVolume(m_audio_volume);
	}
	config_file.close();
}

void Config::saveConfiguration()
{
	Json::Value root;
	Json::Reader reader;
	Json::StyledStreamWriter writer;
	ifstream config_file_i(CONFIG_FILE_NAME);

	bool parsing_successful = reader.parse(config_file_i, root, false);
	if (!parsing_successful)
	{
		// cout  << reader.getFormatedErrorMessages() << endl;
	}
	root["fullscreen"] = m_fullscreen;
	root["music"] = m_music;
	root["map_sensivity"] = m_map_sensivity;
	root["music_volume"] = m_audio_volume;
	// root["music_volume"] =
	ofstream config_file_o(CONFIG_FILE_NAME);
    writer.write(config_file_o, root);
	config_file_i.close();
	config_file_o.close();
}
