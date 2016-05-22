#ifndef CONFIG_H
#define CONFIG_H

class Config
{
	private:
		Config();
		static Config *m_instance;

		bool m_fullscreen;

	public:
		static Config *getInstance();
		bool getFullscreen();
		void setFullscreen(bool value);

};

#endif