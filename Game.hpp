#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
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
    Game(int width, int height, int cell_size, const char* title);

    // Destructor
    ~Game();

    // Inicializa SDL, crea la ventana y el renderer, y los objetos del juego
    bool initialize();

    // Bucle principal del juego
    void run();

private:
    // Punteros a los objetos de SDL
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Dimensiones de la ventana
    int screen_width;
    int screen_height;

    // Objetos del juego
    Table* game_table;
    Snake* player_snake;
    // ... Podríamos añadir Food* game_food; más adelante
    Point food_position;

    // Estado del juego
    GameState current_state;
    bool is_running; // Controla el bucle principal

    // Velocidad del juego (cuántos milisegundos entre actualizaciones lógicas)
    Uint32 game_speed_ms;

    // Métodos privados para la gestión interna del juego
    void handle_input();   // Procesa las entradas del usuario
    void update();         // Actualiza la lógica del juego
    void render();         // Dibuja todos los elementos en pantalla
    void cleanup();        // Libera los recursos de SDL y los objetos del juego

    // Métodos específicos de la lógica del juego de la serpiente
    void generate_food();       // Genera una nueva posición para la comida
    bool check_collision();     // Comprueba colisiones (paredes, consigo misma)
    bool check_food_eaten();    // Comprueba si la serpiente comió la comida
};

#endif // GAME_HPP
