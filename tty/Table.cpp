#include "Table.hpp"
#include <iostream>

Table::Table (int width, int height) {
	dimension.x = width;
	dimension.y = height;
}

Table :: ~Table(){
	std::cout << "Table destroyed." << std::endl;
}

void Table::render (){
    // Dibujar los bordes del tablero
    mvaddch(0,dimension.x-1,ACS_URCORNER);
    for(int y = 1; y<dimension.y-1; ++y){
	    mvaddch(y,0,ACS_VLINE);
	    mvaddch(y,dimension.x-1,ACS_VLINE);
    }
    mvaddch(dimension.y-1,0,ACS_LLCORNER);
    for (int x = 1; x<dimension.x-1; ++x){
	    mvaddch(0,x,ACS_HLINE);
	    mvaddch(dimension.y-1,x,ACS_HLINE);
    }
    mvaddch(0,0,ACS_ULCORNER);
    mvaddch(dimension.y-1,dimension.x-1,ACS_LRCORNER);
}

bool Table::is_inside( int x, int y){
	return x>1 && x<dimension.x-1 && y>1 && y<dimension.y-1;
}

