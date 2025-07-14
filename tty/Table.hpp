#ifndef TABLE_HPP
#define TABLE_HPP

#include <ncurses.h>
#include "Snake.hpp"

class Table {
	public:
		Table(int width, int height);
		//destructor
		~Table();
		//va a dibujar el tablero
		void render ();
		bool is_inside(int x, int y);
		int get_width() const { return dimension.x; }
		int get_height() const { return dimension.y; }
	private:
		//dimension en termino de celdas, para manejar la logica de juego
		Point dimension;
};
#endif
