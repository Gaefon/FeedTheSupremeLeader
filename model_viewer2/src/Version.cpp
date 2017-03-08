#include <Version.h>

#include <vulkan/vulkan.h>

#include <sstream>	

using namespace std;

namespace GEngine
{
	int Version::makeVersion(int major, int minor, int patch)
	{
		return VK_MAKE_VERSION(major, minor, patch);
	}
	
	string Version::versionToString(int version)
	{
		int major = VK_VERSION_MAJOR(version);
		int minor = VK_VERSION_MINOR(version);
		int patch = VK_VERSION_PATCH(version);
		
		stringstream ret;
		ret << major << "." << minor << "." << patch;
		return ret.str();
	}
}
