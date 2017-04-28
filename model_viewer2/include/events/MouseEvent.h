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
				position = 0
			};
	
		private:
			double x_pos;
			double y_pos;
			Type event_type;
		public:
			MouseEvent(Type type);
			~MouseEvent();
			
			void setType(Type type);
			void setPos(double x, double y);
			
			Type getType();
			double getPosX();
			double getPosY();
	};
}

#endif
