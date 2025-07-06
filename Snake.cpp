#include "Snake.hpp"
#include <iostream>

Snake::Snake(int startX, int startY) {
	//empieza con 3 partes
	body.push_back({startX,startY}); //cabeza
	body.push_back({startX -1, startY});
	body.push_back({startX-2, startY});
	// le doy una direccion por defecto
	currentDirection = Direction::RIGHT;
	// empieza sin haber crecido
	hasGrown = false;
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
}

void Snake::grow(){
	hasGrown = true;
}

void Snake::changeDirection(Direction newdir){
	if ((currentDirection == Direction::UP && newdir != Direction::DOWN) &&
	    (currentDirection == Direction::DOWN && newdir != Direction::UP) &&
	    (currentDirection == Direction::LEFT &&newdir != Direction::RIGHT) &&
	    (currentDirection == Direction::RIGHT && newdir != Direction::LEFT)){
		currentDirection = newdir;
	}
}

Point Snake::getHeadPosition() const {
	return body[0];
}

Const std::vector<Point>& Snake::getBody() const{
	return body;
}

bool Snake::checkCollision() const{
	Point head = body[0];
	for(size_t i = 3; i<body.size();++i) {
		if(head.x == body[i].x && head.y == body[i].y) {
			return true;
		}
	}
	//acá falta la logica para revisar si choca contra los limites del tablero, si es que vamos a utilizar esa mecanica
	return false;
}
