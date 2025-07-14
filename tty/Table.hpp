#ifndef TABLE_HPP
#define TABLE_HPP

#include <ncurses.h>
#include "Snake.hpp"

class Table {
	public:
		Table(int width, int height, int cell_siz, int offset_x, int offset_y);
		//destructor
		~Table();
		//va a dibujar el tablero
		void render (SDL_Renderer* renderer);
		bool is_inside(int x, int y);
		SDL_Rect get_cell_rect(int x, int y);
		int get_width() const { return dimension.x; }
		int get_height() const { return dimension.y; }
		int get_cell_size() const { return cell_size; }
		SDL_Rect get_rect() const { return rect; }

	private:
		//dimension en termino de celdas, para manejar la logica de juego
		Point dimension;
		int cell_size;
		SDL_Color background_color;
		SDL_Color border_color;
		//esto representa el area en pixeles que ocupa el tablero en la ventana
		//util para renderizar el fondo y bordes
		SDL_Rect rect;
};
#endif
