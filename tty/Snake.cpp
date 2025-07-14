#include "Snake.hpp"
#include <iostream>

Snake::Snake(int startX, int startY) {
	//empieza con 3 partes
	body.push_back({startX,startY}); //cabeza
	body.push_back({startX -1, startY});
	body.push_back({startX-2, startY});
	// le doy una direccion por defecto
	currentDirection = Direction::RIGHT;
	nextDirection = currentDirection;
	// empieza sin haber crecido
	hasGrown = false;
	headColor = {0, 255, 0, 0};
	bodyColor = {20, 20, 20, 20};
}

void Snake::move(){
	Point head = body[0];
	//calcular la nueva posicion de la cabeza basandose
	//en la direccion
	switch(currentDirection){
		case Direction::UP:	head.y--; break;
		case Direction::DOWN:	head.y++; break;
		case Direction::LEFT:	head.x--; break;
		case Direction::RIGHT:	head.x++; break;
	}
	//inserta la nueva cabeza al principio del vector
	body.insert(body.begin(), head);
	if(!hasGrown) {
		body.pop_back();
	} else {
		hasGrown = false;
	}
	currentDirection = nextDirection;
}

void Snake::grow(){
	hasGrown = true;
}

void Snake::render(SDL_Renderer* render,int cell_siz, int offset_x, int offset_y){
 if (!render) {
        std::cerr << "Error: Renderer es nulo en Snake::render." << std::endl;
        return;
    }

    // Dibuja la cabeza de la serpiente
    SDL_SetRenderDrawColor(render, headColor.r, headColor.g, headColor.b, headColor.a);
    SDL_Rect head_rect;
    head_rect.x = offset_x + body.front().x * cell_siz;
    head_rect.y = offset_y + body.front().y * cell_siz;
    head_rect.w = cell_siz;
    head_rect.h = cell_siz;
    SDL_RenderFillRect(render, &head_rect);

    // Dibuja el resto del cuerpo de la serpiente
    SDL_SetRenderDrawColor(render, bodyColor.r, bodyColor.g, bodyColor.b, bodyColor.a);
    for (size_t i = 1; i < body.size(); ++i) { // Empezamos desde el segundo segmento (índice 1)
        SDL_Rect body_segment_rect;
        body_segment_rect.x = offset_x + body[i].x * cell_siz;
        body_segment_rect.y = offset_y + body[i].y * cell_siz;
        body_segment_rect.w = cell_siz;
        body_segment_rect.h = cell_siz;
        SDL_RenderFillRect(render, &body_segment_rect);
    }
}

void Snake::changeDirection(Direction newdir){
	if ((currentDirection == Direction::UP && newdir != Direction::DOWN) ||
	    (currentDirection == Direction::DOWN && newdir != Direction::UP) ||
	    (currentDirection == Direction::LEFT &&newdir != Direction::RIGHT) ||
	    (currentDirection == Direction::RIGHT && newdir != Direction::LEFT)){
		nextDirection = newdir;
	}
}

Point Snake::getHeadPosition() const {
	return body[0];
}

const std::vector<Point>& Snake::getBody() const{
	return body;
}

bool Snake::checkCollision() const{
	Point head = body[0];
	for(size_t i = 3; i<body.size();++i) {
		if(head.x == body[i].x && head.y == body[i].y) {
			return true;
		}
	}
	return false;
}

bool Snake::checkCollision(Point dot){
	for (size_t i = 0; i<body.size();++i){
		if (body[i].x == dot.x && body[i].y == dot.y){
			return true;
		}
	}
	return false;
}
