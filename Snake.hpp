#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <SDL.h>

struct Point {
	int x;
	int y;
};

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake {
	public:
		Snake (int startX, int startY);
		void move();
		void grow();
		void changeDirection(Direction newdir);
		Point getHeadPosition() const;
		const std::vector<Point>& getBody() const; // devuelve todos los segmentos del cuerpo
		bool checkCollision() const; // revisa si hay colision consigo misma
		void render(SDL_Renderer* render,int cell_siz, int offset_x, int offset_y);

	private:
		std::vector<Point> body;
		Direction currentDirection;
		bool hasGrown;
		SDL_Color headColor;
		SDL_Color bodyColor;
}

#endif
