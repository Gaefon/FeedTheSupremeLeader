#ifndef MAP_H
#define MAP_H


class Map
{
	private:
		unsigned int m_width;
		unsigned int m_height;
	public:
		Map();
		virtual ~Map();

		void setWidth(unsigned int val);
		unsigned int getWidth();
		void setHeight(unsigned int val);
		unsigned int getHeight();

		void drawMap(SDL_Surface *area);
};

#endif // MAP_H
