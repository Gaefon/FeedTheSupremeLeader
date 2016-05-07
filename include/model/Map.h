#ifndef MAP_H
#define MAP_H


class Map
{
	public:
		Map();
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();
	protected:
	private:
		unsigned int m_width;
		unsigned int m_height;
};

#endif // MAP_H
