#ifndef CONFIG_H
#define CONFIG_H

#include <utilities/Singleton.hpp>
#include <lib/jsonCpp/json.h>
#include <iostream>
#include <fstream>

class Config : public Singleton<Config>
{
	friend class Singleton<Config>;

	public:
		enum Variable
		{
			Fullscreen,
			Music,
			MapSensivity,
			AudioVolume,
			SoundsEffects
		};
	private:
		Config();

		bool m_fullscreen;
		bool m_music;
		bool m_sounds_effects;
		int m_map_sensivity;
		int m_audio_volume;

	public:
		void set(Variable var, bool value);
		void set(Variable var, int value);
		bool getBool(Variable var);
		int getInt(Variable var);
		void saveConfiguration();
		void readConfiguration();

};

#endif
