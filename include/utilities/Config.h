#ifndef CONFIG_H
#define CONFIG_H

#include <utilities/Singleton.hpp>

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

};

#endif