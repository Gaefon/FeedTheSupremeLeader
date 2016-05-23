#include <iostream>
#include <uiclass/InterfaceSetup.hpp>
#include <Constants.hpp>
using namespace std;

InterfaceSetup::InterfaceSetup()
{
    m_map_area_y = 0;
    m_map_area_x = 0;
    m_map_area_width = WINDOW_DEFAULT_WIDTH;
    m_map_area_height = WINDOW_DEFAULT_HEIGHT;
    m_horiz_interface_size = 0;
    m_vert_right_interface_size = 0;
    m_vert_left_interface_size = 0;
    m_tooltip_origin = 0;
    m_tooltip_height = 0;
    m_tooltip_width = 0;
}


void InterfaceSetup::getMapArea(unsigned int *x, unsigned int *y, unsigned int *width, unsigned int *length)
{
    *x = m_map_area_x;
    *y = m_map_area_y;
    *width = m_map_area_width;
    *length = m_map_area_height;
}

void InterfaceSetup::setMapArea(unsigned int *x, unsigned int *y, unsigned int *width, unsigned int *length)
{
    m_map_area_x = *x;
    m_map_area_y = *y;
    m_map_area_width = *width;
    m_map_area_height = *length;
}

SDL_Surface *InterfaceSetup::getMapDrawSurface()
{
    SDL_Surface *map_surface = SDL_CreateRGBSurface(0, m_map_area_width, m_map_area_height, 32,0,0,0,0);
    return map_surface;
}

void InterfaceSetup::getHorizInterfaceSize(unsigned int *i_size)
{
    *i_size = m_horiz_interface_size;
}

void InterfaceSetup::setHorizInterfaceSize(unsigned int *i_size)
{
    m_horiz_interface_size = *i_size;
}

void InterfaceSetup::getVertInterfacesSize(unsigned int *right_size, unsigned int *left_size)
{
    m_vert_right_interface_size = *right_size;
    m_vert_left_interface_size = *left_size;
}

void InterfaceSetup::setVertInterfacesSize(unsigned int *right_size, unsigned int *left_size)
{
    m_vert_right_interface_size = *right_size;
    m_vert_left_interface_size = *left_size;
}

void InterfaceSetup::getTooltipLocationInfo(unsigned int *origin, unsigned int *width, unsigned int *height)
{
    *origin = m_tooltip_origin;
    *width = m_tooltip_width;
    *height = m_tooltip_height;
}

void InterfaceSetup::setTooltipLocationInfo(unsigned int *origin, unsigned int *width, unsigned int *height)
{
    m_tooltip_origin = *origin;
    m_tooltip_width = *width;
    m_tooltip_height = *height;
}
