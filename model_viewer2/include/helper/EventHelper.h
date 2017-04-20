#ifndef EVENT_HELPER_H
#define EVENT_HELPER_H

#include <events/KeyEvent.h>

namespace GEngine
{
	class EventHelper
	{
		public:
			static KeyEvent::Key keyFromInt(int value);
			static int modFromInt(int value);
	};
}

#endif
