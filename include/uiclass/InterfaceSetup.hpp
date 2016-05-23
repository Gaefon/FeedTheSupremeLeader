#ifndef INTERFACESETUP_HPP
#define INTERFACESETUP_HPP
#include <utilities/Singleton.hpp>
#include <SDL.h>

class InterfaceSetup : public Singleton<InterfaceSetup>
{
    friend class Singleton<InterfaceSetup>;

    private:
        unsigned int m_map_area_x;
        unsigned int m_map_area_y;
        unsigned int m_map_area_width;
        unsigned int m_map_area_height;
        unsigned int m_horiz_interface_size;
        unsigned int m_vert_right_interface_size;
        unsigned int m_vert_left_interface_size;
        unsigned int m_tooltip_origin;
        unsigned int m_tooltip_height;
        unsigned int m_tooltip_width;
        InterfaceSetup(const InterfaceSetup&){}
        InterfaceSetup();
    public:
        void getMapArea(unsigned int *x, unsigned int *y, unsigned int *width, unsigned int *height);
        void setMapArea(unsigned int *x, unsigned int *y, unsigned int *width, unsigned int *height);
        SDL_Surface *getMapDrawSurface();
        void getHorizInterfaceSize(unsigned int *i_size);
        void setHorizInterfaceSize(unsigned int *i_size);
        void getVertInterfacesSize(unsigned int *right_size, unsigned int *left_size);
        void setVertInterfacesSize(unsigned int *right_size, unsigned int *left_size);
        void getTooltipLocationInfo(unsigned int *origin, unsigned int *width, unsigned int *height);
        void setTooltipLocationInfo(unsigned int *origin, unsigned int *width, unsigned int *height);



};
#include<utilities/Singleton.inc>
#endif // INTERFACESETUP_HPP
