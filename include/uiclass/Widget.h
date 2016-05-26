#ifndef WIDGET_H
#define WIDGET_H

class Widget
{
	public:
		Widget() {}
		~Widget() {}
		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void draw() = 0;
};

#endif