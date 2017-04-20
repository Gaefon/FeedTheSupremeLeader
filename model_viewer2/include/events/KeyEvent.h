#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include <GLFW/glfw3.h>

namespace GEngine
{
	class KeyEvent
	{
		public:
			enum class Key : int
			{
				unknown = -1,
				space = GLFW_KEY_SPACE, 
				apostrophe = GLFW_KEY_APOSTROPHE,
				minus = GLFW_KEY_MINUS,
				
				comma = GLFW_KEY_COMMA,
				period = GLFW_KEY_PERIOD,
				slash = GLFW_KEY_SLASH,
				semicolon = GLFW_KEY_SEMICOLON,
				equal = GLFW_KEY_EQUAL,
				
				backslash = GLFW_KEY_BACKSLASH,
				grave_accent = GLFW_KEY_GRAVE_ACCENT,
				left_bracket = GLFW_KEY_LEFT_BRACKET,
				right_bracket = GLFW_KEY_RIGHT_BRACKET,
				
				_0 = GLFW_KEY_0,
				_1 = GLFW_KEY_1,
				_2 = GLFW_KEY_2,
				_3 = GLFW_KEY_3,
				_4 = GLFW_KEY_4,
				_5 = GLFW_KEY_5,
				_6 = GLFW_KEY_6,
				_7 = GLFW_KEY_7,
				_8 = GLFW_KEY_8,
				_9 = GLFW_KEY_9,
				
				num_lock = GLFW_KEY_NUM_LOCK,
				kp0 = GLFW_KEY_KP_0,
				kp1 = GLFW_KEY_KP_1,
				kp2 = GLFW_KEY_KP_2,
				kp3 = GLFW_KEY_KP_3,
				kp4 = GLFW_KEY_KP_4,
				kp5 = GLFW_KEY_KP_5,
				kp6 = GLFW_KEY_KP_6,
				kp7 = GLFW_KEY_KP_7,
				kp8 = GLFW_KEY_KP_8,
				kp9 = GLFW_KEY_KP_9,
				kpdecimal = GLFW_KEY_KP_DECIMAL,
				kpdivide = GLFW_KEY_KP_DIVIDE,
				kpmultiply = GLFW_KEY_KP_MULTIPLY,
				kpsubstract = GLFW_KEY_KP_SUBTRACT,
				kpadd = GLFW_KEY_KP_ADD,
				kpenter = GLFW_KEY_KP_ENTER,
				kpequal = GLFW_KEY_KP_EQUAL,
				
				a = GLFW_KEY_A,
				b = GLFW_KEY_B,
				c = GLFW_KEY_C,
				d = GLFW_KEY_D,
				e = GLFW_KEY_E,
				f = GLFW_KEY_F,
				g = GLFW_KEY_G,
				h = GLFW_KEY_H,
				i = GLFW_KEY_I,
				j = GLFW_KEY_J,
				k = GLFW_KEY_K,
				l = GLFW_KEY_L,
				m = GLFW_KEY_M,
				n = GLFW_KEY_N,
				o = GLFW_KEY_O,
				p = GLFW_KEY_P,
				q = GLFW_KEY_Q,
				r = GLFW_KEY_R,
				s = GLFW_KEY_S,
				t = GLFW_KEY_T,
				u = GLFW_KEY_U,
				v = GLFW_KEY_V,
				w = GLFW_KEY_W,
				x = GLFW_KEY_X,
				y = GLFW_KEY_Y,
				z = GLFW_KEY_Z,
				
				F1 = GLFW_KEY_F1,
				F2 = GLFW_KEY_F2,
				F3 = GLFW_KEY_F3,
				F4 = GLFW_KEY_F4,
				F5 = GLFW_KEY_F5,
				F6 = GLFW_KEY_F6,
				F7 = GLFW_KEY_F7,
				F8 = GLFW_KEY_F8,
				F9 = GLFW_KEY_F9,
				F10 = GLFW_KEY_F10,
				F11 = GLFW_KEY_F11,
				F12 = GLFW_KEY_F12,
				F13 = GLFW_KEY_F13,
				F14 = GLFW_KEY_F14,
				F15 = GLFW_KEY_F15,
				F16 = GLFW_KEY_F16,
				F17 = GLFW_KEY_F17,
				F18 = GLFW_KEY_F18,
				F19 = GLFW_KEY_F19,
				F20 = GLFW_KEY_F20,
				F21 = GLFW_KEY_F21,
				F22 = GLFW_KEY_F22,
				F23 = GLFW_KEY_F23,
				F24 = GLFW_KEY_F24,
				F25 = GLFW_KEY_F25,
				
				escape = GLFW_KEY_ESCAPE,
				enter = GLFW_KEY_ENTER,
				backspace = GLFW_KEY_BACKSPACE,
				
				right = GLFW_KEY_RIGHT,
				left = GLFW_KEY_LEFT,
				up = GLFW_KEY_UP,
				down = GLFW_KEY_DOWN,
				
				page_up = GLFW_KEY_PAGE_UP,
				page_down = GLFW_KEY_PAGE_DOWN,
				insert = GLFW_KEY_INSERT,
				_delete = GLFW_KEY_DELETE,
				home = GLFW_KEY_HOME,
				end = GLFW_KEY_END,
				
				print_screen = GLFW_KEY_PRINT_SCREEN,
				scroll_lock = GLFW_KEY_SCROLL_LOCK,
				pause = GLFW_KEY_PAUSE,
				
				left_shift = GLFW_KEY_LEFT_SHIFT,
				left_control = GLFW_KEY_LEFT_CONTROL,
				left_alt = GLFW_KEY_LEFT_ALT,
				left_super = GLFW_KEY_LEFT_SUPER,
				
				right_shift = GLFW_KEY_RIGHT_SHIFT,
				right_control = GLFW_KEY_RIGHT_CONTROL,
				right_alt = GLFW_KEY_RIGHT_ALT,
				right_super = GLFW_KEY_RIGHT_SUPER,

				tab = GLFW_KEY_TAB,
				caps_lock = GLFW_KEY_CAPS_LOCK
			};
			
			enum class Mod : int
			{
				shift = GLFW_MOD_SHIFT,
				control = GLFW_MOD_CONTROL,
				alt = GLFW_MOD_ALT,
				super = GLFW_MOD_SUPER
			};
		
		private:
			Key value;
			bool pressed;
			int modif;
			
		public:
			KeyEvent(Key val, bool press, int mod);
			~KeyEvent();
			
			void setKey(Key val, bool press, int mod);
			Key getKey();
			bool isPressed();
			bool isMod(Mod mod);
		
		
	};
}

#endif
