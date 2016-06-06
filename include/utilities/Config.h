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
			Fullscreen
		};
	private:
		Config();

		bool m_fullscreen;

	public:
		void set(Variable var, bool value);
		bool get(Variable var);
		void saveConfiguration();
		void readConfiguration();
		
};

#endif
