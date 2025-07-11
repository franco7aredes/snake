// main.cpp
#include "Game.hpp"

int main(int argc, char* argv[]) {
    // Definir las dimensiones de la ventana y el tamaño de las celdas
    // Puedes jugar con estos valores.
    // Aquí, una ventana de 640x480 píxeles, con celdas de 20x20 píxeles.
    // El constructor de Game determinará cuántas celdas caben.
    int window_width = 640;
    int window_height = 480;
    int cell_size = 20; // Tamaño en píxeles de cada celda

    Game myGame(window_width, window_height, cell_size, "Mi Juego de la Serpiente");

    if (!myGame.initialize()) {
        // Manejar error de inicialización
        return 1;
    }

    myGame.run(); // Inicia el bucle del juego

    // El destructor de myGame se llamará automáticamente al final de main
    // lo que ejecutará cleanup().
    return 0;
}
