#ifndef BUILDING_HPP
#define BUILDING_HPP


class Building
{
	private:
		unsigned int m_width;
		unsigned int m_height;
		std::string m_name;
	public:
		Building();
		virtual ~Building();
		unsigned int getWidth();
		void setWidth(unsigned int val);
		unsigned int getHeight();
		void setHeight(unsigned int val);
		std::string getName();
		void setName(std::string val);
		virtual void drawBuilding() = 0;
};

#endif // BUILDING_HPP
