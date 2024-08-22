# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude -Wall -Wextra

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/src

# Archivos fuente y de cabecera
CHAT_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
CHAT_OBJS = $(CHAT_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(BUILD_DIR)/main.o

# Archivo ejecutable
TARGET = $(BUILD_DIR)/chat

# Regla por defecto
all: $(BUILD_DIR) $(TARGET)

# Regla para crear los directorios de compilación
$(BUILD_DIR):
	mkdir -p $(OBJ_DIR)

# Regla para compilar el ejecutable
$(TARGET): $(CHAT_OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el archivo objeto de main.cpp
$(MAIN_OBJ): main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR)

# Ejecutar el servidor
run-servidor: $(TARGET)
	./$(TARGET) servidor 12347 12349

# Ejecutar el cliente
run-cliente: $(TARGET)
	./$(TARGET) cliente 127.0.0.1 12347

# Ejecutar el monitor
run-monitor: $(TARGET)
	./$(TARGET) monitor 127.0.0.1 12349

# Declarar reglas como phony
.PHONY: all clean run-servidor run-cliente run-monitor


