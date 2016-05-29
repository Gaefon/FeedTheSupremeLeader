#include <uiclass/Widget.h>

Widget::Widget(MainWindow *parent)
{
	m_parent = parent;
}

Widget::~Widget()
{
}

MainWindow *Widget::getParent()
{
	return m_parent;
}
