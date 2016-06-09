#include <uiclass/Widget.h>

Widget::Widget(MainWindow *parent)
{
	m_parent = parent;
	m_is_visible = true;
}

Widget::~Widget()
{
}

void Widget::hide()
{
	m_is_visible = false;
}

void Widget::show()
{
	m_is_visible = true;
}

bool Widget::isVisible()
{
	return m_is_visible;
}

MainWindow *Widget::getParent()
{
	return m_parent;
}
