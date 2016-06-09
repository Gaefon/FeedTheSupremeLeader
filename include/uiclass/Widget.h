#ifndef WIDGET_H
#define WIDGET_H

#include <uiclass/MainWindow.hpp>

class Widget
{
	private:
		MainWindow *m_parent;
		bool m_is_visible;
	public:
		Widget(MainWindow *parent);
		virtual ~Widget();
		MainWindow *getParent();
		void hide();
		void show();
		bool isVisible();
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void draw() = 0;
};

#endif