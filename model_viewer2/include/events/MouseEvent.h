#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

namespace GEngine
{
	class MouseEvent
	{
		public:
			enum class Type : int
			{
				unknown = -1,
				position = 0,
				leftButton = 1,
				rightButton = 2,
				middleButton = 3,
				scroll = 4
			};
	
		private:
			double x_pos;
			double y_pos;
			
			double x_offset;
			double y_offset;
			
			Type event_type;
			bool is_pressed;
			
		public:
			MouseEvent(Type type);
			~MouseEvent();
			
			void setType(Type type);
			void setPos(double x, double y);
			void setOffset(double x, double y);
			void setPressed(bool new_val);
			
			Type getType();
			double getPosX();
			double getPosY();
			
			double getOffsetX();
			double getOffsetY();
			
			bool isPressed();
	};
}

#endif
