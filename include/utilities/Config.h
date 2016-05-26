#ifndef CONFIG_H
#define CONFIG_H

#include <utilities/Singleton.hpp>

class Config : public Singleton<Config>
{
	friend class Singleton<Config>;

	private:
		Config();

		bool m_fullscreen;

	public:
		bool getFullscreen();
		void setFullscreen(bool value);

};

#endif