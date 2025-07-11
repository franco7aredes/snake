#include "Game.hpp"
#include <iostream> 
#include <random>  
#include <chrono> 

// Constructor
Game::Game(int width, int height, int cell_size, const char* title)
    : window(nullptr),
      renderer(nullptr),
      screen_width(width),
      screen_height(height),
      game_table(nullptr),
      player_snake(nullptr),
      current_state(RUNNING),
      is_running(false),
      game_speed_ms(150) // Velocidad inicial de la serpiente (ms por movimiento)
{
    // El constructor solo inicializa variables miembro.
    // La inicialización de SDL y la creación de objetos se hacen en initialize().
    std::cout << "Game object created." << std::endl;
}

// Destructor
Game::~Game() {
    cleanup(); // Aseguramos que los recursos se liberen al destruir el objeto Game
    std::cout << "Game object destroyed." << std::endl;
}

// Inicializa SDL, ventana, renderer y objetos del juego
bool Game::initialize() {
    // 1. Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // 2. Crear ventana
    window = SDL_CreateWindow("Snake Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_width,
                              screen_height,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // 3. Crear renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // 4. Inicializar objetos del juego
    // Offset para el tablero (podrías centrarlo, dejar un margen, etc.)
    // Aquí, por simplicidad, el tablero ocupa toda la ventana.
    // Si quieres un margen, ajusta el offset_x y offset_y, y calcula el ancho/alto del tablero
    // en relación a la ventana y los márgenes deseados.
    int table_offset_x = 0;
    int table_offset_y = 0;

    // Ajustamos las dimensiones de la tabla para que encajen en la ventana con un margen, si lo deseas.
    // Para este ejemplo, haremos que la tabla sea un poco más pequeña que la ventana
    // o que las dimensiones de la tabla coincidan con las de la ventana si lo estableciste así.
    int table_width_cells = screen_width / (screen_height / 20); // Ejemplo: 20 celdas de alto, calcular ancho proporcional
    int table_height_cells = screen_height / (screen_height / 20); // Ejemplo: 20 celdas de alto
    int table_cell_size = screen_height / 20; // Tamaño de celda basado en la altura de la ventana para que sea cuadrada.

    // Podrías ajustar table_width_cells y table_height_cells a valores fijos como 30x20
    // y luego calcular el screen_width/height basado en eso y el cell_size.
    // O puedes hacer que el tablero ocupe la ventana completa con las dimensiones dadas.
    // Por ahora, asumamos que las dimensiones `width` y `height` pasadas al constructor de Game
    // son las dimensiones *en celdas* del tablero y la ventana se ajustará.
    // O mejor, las dimensiones de la ventana y de la celda, y calculamos las celdas:
    table_cell_size = 20; // Por ejemplo, cada celda de 20x20 píxeles
    table_width_cells = screen_width / table_cell_size;
    table_height_cells = screen_height / table_cell_size;


    game_table = new Table(table_width_cells, table_height_cells, table_cell_size, table_offset_x, table_offset_y);
    player_snake = new Snake(table_width_cells / 2, table_height_cells / 2); // Serpiente empieza en el centro
    // ... game_food = new Food(); // Si decides crear una clase Food

    // 5. Generar la primera comida (asumiendo que Snake.hpp tiene un miembro para la comida o que la manejarás aquí)
    // Por ahora, lo dejamos pendiente hasta definir cómo manejar la comida.

    is_running = true;
    std::cout << "Game initialized successfully." << std::endl;
    return true;
}

// Bucle principal del juego
void Game::run() {
    if (!is_running) {
        std::cerr << "Game not initialized. Call initialize() first." << std::endl;
        return;
    }

    Uint32 last_update_time = SDL_GetTicks(); // Tiempo del último update

    // Bucle principal
    while (is_running) {
        handle_input(); // Siempre manejar entrada

        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_update_time >= game_speed_ms) {
            update(); // Actualizar lógica solo si ha pasado suficiente tiempo
            last_update_time = current_time;
        }

        render(); // Siempre renderizar

        // Control de FPS (opcional, SDL_RENDERER_PRESENTVSYNC ya lo hace en cierta medida)
        // SDL_Delay(1); // Pequeño delay para no consumir CPU al máximo
    }
}

// Maneja la entrada del usuario
void Game::handle_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false; // El usuario cerró la ventana
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    player_snake->change_direction(UP);
                    break;
                case SDLK_DOWN:
                    player_snake->change_direction(DOWN);
                    break;
                case SDLK_LEFT:
                    player_snake->change_direction(LEFT);
                    break;
                case SDLK_RIGHT:
                    player_snake->change_direction(RIGHT);
                    break;
                case SDLK_p: // Pausar/Reanudar
                    if (current_state == RUNNING) {
                        current_state = PAUSED;
                    } else if (current_state == PAUSED) {
                        current_state = RUNNING;
                    }
                    break;
                // Otros controles como reiniciar, etc.
            }
        }
    }
}

// Actualiza la lógica del juego
void Game::update() {
    if (current_state != RUNNING) {
        return; // No actualizar si el juego está pausado o terminado
    }

    player_snake->move(); // Mueve la serpiente

    if (check_collision()) {
        current_state = GAME_OVER;
        std::cout << "GAME OVER! Collision detected." << std::endl;
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(renderer);

    // Dibujar el tablero
    if (game_table) {
        game_table->render(renderer);
    }

    // Dibujar la serpiente
    if (player_snake) {
        // Necesitamos una forma de que Snake dibuje sus segmentos usando el table->get_cell_rect
        // Pasaremos el renderer y el table para que Snake pueda obtener las coordenadas correctas
        player_snake->render(renderer, game_table->get_cell_size(), game_table->get_rect().x, game_table->get_rect().y);
    }

    // Dibujar la comida (esto es un placeholder, asume que la comida se maneja en Game o tiene su propia clase)
    // Para la comida, necesitaremos una coordenada Point food_position; en Game
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo para la comida
    // SDL_Rect food_rect = game_table->get_cell_rect(food_position.x, food_position.y);
    // SDL_RenderFillRect(renderer, &food_rect);


    // Renderizar texto de "Game Over" o "Pausa"
    if (current_state == GAME_OVER) {
        // Aquí podrías renderizar texto "GAME OVER"
        // Requiere SDL_ttf, que no hemos inicializado. Por ahora, solo un mensaje en consola.
    } else if (current_state == PAUSED) {
        // Aquí podrías renderizar texto "PAUSED"
    }

    // Presentar lo dibujado en pantalla
    SDL_RenderPresent(renderer);
}

// Libera los recursos de SDL y los objetos del juego
void Game::cleanup() {
    delete player_snake;
    player_snake = nullptr;

    delete game_table;
    game_table = nullptr;

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
    std::cout << "Game resources cleaned up." << std::endl;
}

// --- Métodos específicos del juego de la serpiente  ---

void Game::generate_food() {
    // Genera una posición aleatoria para la comida dentro de los límites del tablero
    // Asegúrate de que no aparezca en la misma posición que la serpiente
    // Necesitarás una variable `Point food_position;` en Game.hpp
    // Y un generador de números aleatorios.
    // Ejemplo muy básico (sin verificar colisión con la serpiente):

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, game_table->get_width() - 1);
    std::uniform_int_distribution<> dis_y(0, game_table->get_height() - 1);
    food_position.x = dis_x(gen);
    food_position.y = dis_y(gen);
    std::cout << "Food generated at: (" << food_position.x << ", " << food_position.y << ")" << std::endl;
}

bool Game::check_collision() {
    // 1. Colisión con los bordes del tablero
    Point head_pos = player_snake->get_head_position();
    // 2. Colisión consigo misma 
    return !(game_table->is_inside(head_pos-x, head_pos.y)) ||
	    player_snake->checkCollision();

}

bool Game::check_food_eaten() {
    // Comprueba si la cabeza de la serpiente está en la misma posición que la comida
    return player_snake->getHeadPosition().x == food_position.x &&
	    player_snake->getHeadPosition().y == food_position.y;
}
