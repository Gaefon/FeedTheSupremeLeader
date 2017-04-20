#include <events/KeyEvent.h>

namespace GEngine
{
	KeyEvent::KeyEvent(KeyEvent::Key val, bool press, int mod)
	{
		setKey(val, press, mod);
	}
	
	KeyEvent::~KeyEvent()
	{}
	
	void KeyEvent::setKey(Key val, bool press, int mod)
	{
		value = val;
		pressed = press;
		modif = mod;
	}
	
	KeyEvent::Key KeyEvent::getKey()
	{
		return value;
	}
	
	bool KeyEvent::isPressed()
	{
		return pressed;
	}
	
	bool KeyEvent::isMod(KeyEvent::Mod mod)
	{
		if (modif & (int) mod)
			return true;
		return false;
	}
}
