#include <Constants.hpp>
#include <uiclass/GameMenuDialog.h>
#include <utilities/RessourceManager.h>
#include <utilities/sounds/sounds.h>
#include <utilities/Config.h>

GameMenuDialog::GameMenuDialog(MainWindow *parent, SDLPoller *poller, int w, int h): Widget(parent)
{
	m_width = w;
	m_height = h;

	rect_back.x = getParent()->getWidth() / 2 - m_width / 2;
	rect_back.y = getParent()->getHeight() / 2 - m_height / 2;
	rect_back.w = w;
	rect_back.h = h;

	m_is_visible = false;
	m_is_goto_menu_requested = false;

	m_btn_menu = new Button(getParent(), 0, 0, RessourceManager::getInstance()->getSurface(RessourceManager::Menu_Default_Button), "Main menu");
	m_btn_menu->setPosition(getParent()->getWidth() / 2 - m_btn_menu->getWidth() / 2, getParent()->getHeight() / 2 - m_height / 2 + 40);

	m_poller = poller;
}

GameMenuDialog::~GameMenuDialog()
{
	delete m_btn_menu;
}

void GameMenuDialog::registerButtons()
{
	m_poller->subscribe(m_btn_menu);
}

void GameMenuDialog::unregisterButton()
{
	m_poller->unSubscribe(m_btn_menu);
}

int GameMenuDialog::getWidth()
{
	return m_width;
}

int GameMenuDialog::getHeight()
{
	return m_height;
}

bool GameMenuDialog::isGotoMenuRequested()
{
	return m_is_goto_menu_requested;
}

void GameMenuDialog::draw()
{
	if (m_is_visible)
	{
		if (m_btn_menu->isClicked())	{
			if (Config::getInstance()->getBool(Config::Music)) {
					Sounds::getInstance()->loadMusic(MENU_MUSIQUE);
			}
				m_is_goto_menu_requested = true;
		}
		SDL_SetRenderDrawColor(getParent()->getRenderer(), 48, 48, 48, 255);
		SDL_RenderFillRect(getParent()->getRenderer(), &rect_back);
		m_btn_menu->draw();
	}
}

bool GameMenuDialog::onSdlEventReceived(SDL_Event event)
{
	if (event.key.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
	{
		m_is_visible = !m_is_visible;
		if (m_is_visible)
			registerButtons();
		else
			unregisterButton();
		return true;
	}
	if (m_is_visible)
	{
	}
	return false;
}
