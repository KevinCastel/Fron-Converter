CC = gcc
CFLAGS = -I../include -Wall -Wextra -O2
SRC_DIR = ./src
BIN_DIR = ./bin

# Recherche tous les fichiers .c dans SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.c)
# Déduit les noms des fichiers objets correspondants dans BIN_DIR
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCES))

# Nom de l'exécutable final
TARGET = $(BIN_DIR)/app

# Cible par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Règle pour créer les fichiers objets
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)
