#include "Game.hpp"
#include <iostream> 
#include <random>  
#include <chrono> 

// Constructor
Game::Game()
    : game_table(nullptr),
      player_snake(nullptr),
      game_speed_ms(150), // Velocidad inicial de la serpiente (ms por movimiento)
      current_state(RUNNING),
      is_running(false)
{
    // El constructor solo inicializa variables miembro.
    // Los valores de la ventana se obtendrán en el initialize
    std::cout << "Game object created." << std::endl;
}

// Destructor
Game::~Game() {
    cleanup(); // Aseguramos que los recursos se liberen al destruir el objeto Game
    std::cout << "Game object destroyed." << std::endl;
}

// Inicializa SDL, ventana, renderer y objetos del juego
bool Game::initialize() {
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	timeout(game_speed_ms);
	getmaxyx(stdscr, screen_height, screen_width);
	game_table = new Table(screen_width, screen_height);
	player_snake = new Snake (screen_width/2, screen_height/2);
	generate_food();
	is_running = true;
	return true;
}

// Bucle principal del juego
void Game::run() {
    if (!is_running) {
        std::cerr << "Game not initialized. Call initialize() first." << std::endl;
        return;
    }


    // Bucle principal
    while (is_running) {
        handle_input(); // Siempre manejar entrada
        update(); 
        render(); // Siempre renderizar

    }
}

// Maneja la entrada del usuario
void Game::handle_input() {
    int ch = getch();
    if (ch == ERR){
	    return;
    }
    switch (ch){
    	case 'w':
        	player_snake->changeDirection(Direction::UP);
                break;
        case 's':
                player_snake->changeDirection(Direction::DOWN);
                break;
        case 'a':
                player_snake->changeDirection(Direction::LEFT);
                break;
        case 'd':
                player_snake->changeDirection(Direction::RIGHT);
                break;
        case 'p': // Pausar/Reanudar
                if (current_state == RUNNING) {
             	   current_state = PAUSED;
                } else if (current_state == PAUSED) {
                   current_state = RUNNING;
                }
                break;
                // Otros controles como reiniciar, etc.
            }
}

// Actualiza la lógica del juego
void Game::update() {
    if (current_state != RUNNING) {
        return; // No actualizar si el juego está pausado o terminado
    }

    player_snake->move(); // Mueve la serpiente
    handle_input();

    if (check_collision()) {
        current_state = GAME_OVER;
        // is_running = false; // Puedes terminar el juego o mostrar una pantalla de game over
    }

    if (check_food_eaten()) {
        player_snake->grow(); // La serpiente crece
        // Aumentar la velocidad o la puntuación aquí
        generate_food(); // Genera nueva comida
    }
}

// Dibuja todos los elementos en pantalla
void Game::render() {
    // Limpiar la pantalla
	clear();

    // Dibujar el tablero
    if (game_table) {
        game_table->render();
    }

    // Dibujar la serpiente
    if (player_snake) {
        player_snake->render();
    }

    // Dibujar la comida 
    mvprintw(food_position.x, food_position.y, "#");

    // Renderizar texto de "Game Over" o "Pausa"
    if (current_state == GAME_OVER) {
        // Aquí podrías renderizar texto "GAME OVER"
    } else if (current_state == PAUSED) {
        // Aquí podrías renderizar texto "PAUSED"
    }

    // Presentar lo dibujado en pantalla
    refresh();
}

// Libera los recursos de SDL y los objetos del juego
void Game::cleanup() {
    delete player_snake;
    player_snake = nullptr;

    delete game_table;
    game_table = nullptr;

    // vuelve la terminal a la normalidad
    endwin();
    std::cout << "Game resources cleaned up." << std::endl;
}

// --- Métodos específicos del juego de la serpiente  ---

void Game::generate_food() {
    // Genera una posición aleatoria para la comida dentro de los límites del tablero
    // no aparece en la misma posición que la serpiente
    // Ejemplo muy básico (verificando colisión con la serpiente):

    bool aux = true;
    while(aux){
    	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> dis_x(0, game_table->get_width() - 1);
    	std::uniform_int_distribution<> dis_y(0, game_table->get_height() - 1);
        food_position.x = dis_x(gen);
        food_position.y = dis_y(gen);
        if (!(player_snake->checkCollision(food_position))){
		aux = false;
        }
    }
}

bool Game::check_collision(Point dot){
	return !(game_table->is_inside(dot.x, dot.y));
	}

bool Game::check_collision() {
    // 1. Colisión con los bordes del tablero
    Point head_pos = player_snake->getHeadPosition();
    // 2. Colisión consigo misma 
    return !(game_table->is_inside(head_pos.x, head_pos.y)) ||
	    player_snake->checkCollision();

}

bool Game::check_food_eaten() {
    // Comprueba si la cabeza de la serpiente está en la misma posición que la comida
    return player_snake->getHeadPosition().x == food_position.x &&
	    player_snake->getHeadPosition().y == food_position.y;
}
