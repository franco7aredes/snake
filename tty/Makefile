# Define el compilador de C++
CXX = g++

# Define las banderas del compilador
# -Wall: Habilita todas las advertencias (muy recomendado para depuración)
# -g: Incluye información de depuración para gdb
# -std=c++17: Usa el estándar C++17 (puedes ajustar a c++11, c++14, c++20 si lo necesitas)
# -O2: Nivel de optimización (para un rendimiento decente en la versión final)
CXXFLAGS = -Wall -g -std=c++17 -O2

# Define las banderas para enlazar ncurses
LDFLAGS = -lncurses

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
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regla para compilar cada archivo .cpp en su archivo .o correspondiente
# $<: El primer pre-requisito (el archivo .cpp)
# $@: El objetivo (el archivo .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados (objetos y ejecutable)
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para garantizar que 'all' no es un nombre de archivo
.PHONY: all clean
