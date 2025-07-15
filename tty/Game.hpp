#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include "Table.hpp" 

// Posibles estados del juego (opcional, pero útil para expandir el juego)
enum GameState {
    RUNNING,
    PAUSED,
    GAME_OVER
};

class Game {
public:
    // Constructor
    Game();

    // Destructor
    ~Game();

    // Inicializa SDL, crea la ventana y el renderer, y los objetos del juego
    bool initialize();

    // Bucle principal del juego
    void run();

private:

    // Dimensiones de la ventana
    int screen_width;
    int screen_height;

    // Objetos del juego
    Table* game_table;
    Snake* player_snake;
    Point food_position;

    uint32_t game_speed_ms;
    // Estado del juego
    GameState current_state;
    bool is_running; // Controla el bucle principal

    // Métodos privados para la gestión interna del juego
    void handle_input();   // Procesa las entradas del usuario
    void update();         // Actualiza la lógica del juego
    void render();         // Dibuja todos los elementos en pantalla
    void cleanup();        // Libera los recursos de SDL y los objetos del juego

    // Métodos específicos de la lógica del juego de la serpiente
    void generate_food();       // Genera una nueva posición para la comida
    bool check_collision();     // Comprueba colisiones (paredes, consigo misma)
    bool check_food_eaten();    // Comprueba si la serpiente comió la comida
    bool check_collision(Point dot); //Comprueba colisiones de la comida
};

#endif // GAME_HPP
