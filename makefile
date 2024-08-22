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
MONITOR_MAIN_OBJ = $(BUILD_DIR)/monitor_main.o

# Archivos ejecutables
TARGET_CHAT = $(BUILD_DIR)/chat
TARGET_MONITOR = $(BUILD_DIR)/monitor

# Regla por defecto
all: $(BUILD_DIR) $(TARGET_CHAT) $(TARGET_MONITOR)

# Regla para crear los directorios de compilación
$(BUILD_DIR):
	mkdir -p $(OBJ_DIR)

# Regla para compilar el ejecutable del chat
$(TARGET_CHAT): $(CHAT_OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar el ejecutable del monitor
$(TARGET_MONITOR): $(CHAT_OBJS) $(MONITOR_MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el archivo objeto de main.cpp
$(MAIN_OBJ): main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar el archivo objeto de monitor_main.cpp
$(MONITOR_MAIN_OBJ): monitor_main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR)

# Ejecutar el servidor
run-servidor: $(TARGET_CHAT)
	./$(TARGET_CHAT) servidor 12347 12349

# Ejecutar el cliente
run-cliente: $(TARGET_CHAT)
	./$(TARGET_CHAT) cliente 127.0.0.1 12347

# Ejecutar el monitor
run-monitor: $(TARGET_MONITOR)
	./$(TARGET_MONITOR) 127.0.0.1 12349

# Declarar reglas como phony
.PHONY: all clean run-servidor run-cliente run-monitor
