#include <helper/EventHelper.h>

namespace GEngine
{
	KeyEvent::Key EventHelper::keyFromInt(int value)
	{
		KeyEvent::Key key = static_cast<KeyEvent::Key>(value);
		
		return key;
		//return KeyEvent::Key::unknown;
	}
	
	int EventHelper::modFromInt(int value)
	{
		int res = 0;
		
		if (value & GLFW_MOD_SHIFT)
			res |= (int) KeyEvent::Mod::shift;
			
		if (value & GLFW_MOD_CONTROL)
			res |= (int) KeyEvent::Mod::control;
			
		if (value & GLFW_MOD_ALT)
			res |= (int) KeyEvent::Mod::alt;
			
		if (value & GLFW_MOD_SUPER)
			res |= (int) KeyEvent::Mod::super;
		
		return res;
	}
}
