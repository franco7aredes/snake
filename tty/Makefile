# Define el compilador de C++
CXX = g++

# Define las banderas del compilador
# -Wall: Habilita todas las advertencias (muy recomendado para depuración)
# -g: Incluye información de depuración para gdb
# -std=c++17: Usa el estándar C++17 (puedes ajustar a c++11, c++14, c++20 si lo necesitas)
# -O2: Nivel de optimización (para un rendimiento decente en la versión final)
CXXFLAGS = -Wall -g -std=c++17 -O2

# Define las banderas para enlazar SDL2
# `sdl2-config --cflags`: Obtiene las banderas de compilación de SDL2 (rutas de inclusión)
# `sdl2-config --libs`: Obtiene las banderas de enlace de SDL2 (bibliotecas a enlazar)
# Asegúrate de que `sdl2-config` esté en tu PATH o especifica la ruta completa
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs)
CURSES = $(shell -lncurses)

# Archivos fuente del proyecto
SRCS = Main.cpp Game.cpp Table.cpp Snake.cpp

# Archivos objeto (se generarán a partir de los .cpp)
# Sustituye la extensión .cpp por .o
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable final
TARGET = snake_game

# --- Reglas de Compilación ---

# Regla por defecto: Compila el ejecutable final
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CURSES)

# Regla para compilar cada archivo .cpp en su archivo .o correspondiente
# $<: El primer pre-requisito (el archivo .cpp)
# $@: El objetivo (el archivo .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CURSES) -c $< -o $@

# Regla para limpiar los archivos generados (objetos y ejecutable)
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para garantizar que 'all' no es un nombre de archivo
.PHONY: all clean
