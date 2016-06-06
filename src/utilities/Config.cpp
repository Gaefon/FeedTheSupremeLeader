#include <iostream>
#include <utilities/Config.h>
#include <Constants.hpp>

using namespace std;

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

void Config::readConfiguration()
{
	ifstream config_file(CONFIG_FILE_NAME);
	Json::Value root;
  Json::Reader reader;

	bool parsing_successful = reader.parse(config_file, root, false);
	if (!parsing_successful)
		return;
	if (root["fullscreen"].isNull() == false) {
		m_fullscreen = root["fullscreen"].asBool();
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
	ofstream config_file_o(CONFIG_FILE_NAME);
    writer.write(config_file_o, root);
	config_file_i.close();
	config_file_o.close();
}
