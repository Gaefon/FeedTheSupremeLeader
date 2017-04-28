#include <events/MouseEvent.h>

namespace GEngine
{
	MouseEvent::MouseEvent(MouseEvent::Type type)
	{
		event_type = type;
		x_pos = -1.0f;
		y_pos = -1.0f;
	}
	
	MouseEvent::~MouseEvent()
	{
	}
	
	void MouseEvent::setType(MouseEvent::Type type)
	{
		event_type = type;
	}
	
	void MouseEvent::setPos(double x, double y)
	{
		x_pos = x;
		y_pos = y;
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
