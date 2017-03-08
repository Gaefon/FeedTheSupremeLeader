#ifndef VERSION_H
#define VERSION_H

#include <string>

namespace GEngine
{
	class Version
	{
		public:
			static int makeVersion(int major, int minor, int patch);
			static std::string versionToString(int version);
	};
}

#endif
