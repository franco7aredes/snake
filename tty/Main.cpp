// main.cpp
#include "Game.hpp"

int main(int argc, char* argv[]) {

    Game myGame; 

    if (!myGame.initialize()) {
        // Manejar error de inicialización
        return 1;
    }

    myGame.run(); // Inicia el bucle del juego

    // El destructor de myGame se llamará automáticamente al final de main
    // lo que ejecutará cleanup().
    return 0;
}
