#ifndef BUILDING_HPP
#define BUILDING_HPP


class Building
{
	public:
		Building();
		virtual ~Building();
		unsigned int getWidth();
		void setWidth(unsigned int val);
		unsigned int getHeight();
		void setHeight(unsigned int val);
	protected:
	private:
		unsigned int m_width;
		unsigned int m_height;
};

#endif // BUILDING_HPP
