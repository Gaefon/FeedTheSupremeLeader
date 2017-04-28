#include <events/MouseEvent.h>

namespace GEngine
{
	MouseEvent::MouseEvent()
	{
		event_type = MouseEvent::Type::unknown;
		x_pos = -1.0f;
		y_pos = -1.0f;
	}
	
	MouseEvent::~MouseEvent()
	{
	}
	
	MouseEvent::Type MouseEvent::getType()
	{
		return event_type;
	}
	
	double MouseEvent::getPosX()
	{
		return x_pos;
	}
	
	double MouseEvent::getPosY()
	{
		return y_pos;
	}
}
