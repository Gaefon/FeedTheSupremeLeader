#ifndef COMMISSAR_H
#define COMMISSAR_H

class Commissar
{
	private:
		SDL_Texture *m_button_commissar;
	public:
		Commissar(MainWindow *prnt, int pos_x, int pos_y);
		~Commissar();
		int getWidth();
		int getHeight();
		void draw();
};

#endif