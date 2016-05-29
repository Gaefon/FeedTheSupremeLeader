#ifndef WIDGET_H
#define WIDGET_H

#include <uiclass/MainWindow.hpp>

class Widget
{
	private:
		MainWindow *m_parent;
	public:
		Widget(MainWindow *parent);
		virtual ~Widget();
		MainWindow *getParent();
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void draw() = 0;
};

#endif