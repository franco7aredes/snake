#include "Table.hpp"
#include <iostream>

Table::Table (int width, int height, int cell_siz, int offset_x= 0,
		int offset_y = 0){
	dimension.x = width;
	dimension.y = height;
	cell_size = cell_siz;
	background_color = {0, 50, 0, 255}; //verde oscuro
	border_color = {255, 255, 255, 255}; //blanco
	//el SDL_rect representa el área total del tablero en pixeles
	rect.x = offset_x;
	rect.y = offset_y;
	rect.w = dimension.x * cell_size;
	rect.h = dimension.y * cell_size;
}

Table :: ~Table(){
	SDL_DestroyRenderer(renderer);
	std::cout << "Table destroyed." << std::endl;
}

void Table::render (SDL_Renderer* renderer){
	if (!renderer){
		std::cerr << "Error: renderer nulo en la función render" << std::endl;
		return;
	}
	// Dibujar el fondo del tablero
	SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
	SDL_RenderFillRect(renderer, &rect);

    // Dibujar los bordes del tablero
	SDL_SetRenderDrawColor(renderer, border_color.r, border_color.g, border_color.b, border_color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

bool Table::is_inside( int x, int y){
	return x>0 && x<dimension.x && y>0 && y<dimension.y;
}

SDL_Rect Table::get_cell_rect (int x, int y){
	SDL_Rect cell_rect;
	cell_rect.x = rect.x + x * cell_size;
	cell_rect.y = rect.y + y * cell_size;
	cell_rect.w = cell_size;
	cell_rect.h = cell_size;
	return cell_rect;
}
