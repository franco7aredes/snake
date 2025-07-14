#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <ncurses.h>

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
		bool checkCollision(Point dot); // auxiliar para evitar que la comida aparezca en la vibora
		void render();

	private:
		std::vector<Point> body;
		Direction currentDirection;
		Direction nextDirection;
		bool hasGrown;
};

#endif
