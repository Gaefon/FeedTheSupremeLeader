#include <GameInterface.h>

GameInterface::GameInterface(MainWindow *parent, SDLPoller *poller)
{
	m_parent = parent;
	m_poller = poller;
	m_map = new Map(m_parent);
	m_poller->subscribe(m_map);
}

GameInterface::~GameInterface()
{
	delete m_map;
}

void GameInterface::draw()
{
	m_map->drawMap();
}