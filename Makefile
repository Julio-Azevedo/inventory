# nome do executável
TARGET = inventory

# compilador
CC = gcc

# flags do compilador
CFLAGS = -Wall -Wextra -g

# diretórios
SRC_DIR = src
MODULES_DIR = modules
BUILD_DIR = build

# lista de arquivos fonte
SOURCES = $(SRC_DIR)/inventory.c $(wildcard $(MODULES_DIR)/*.c)

# lista de arquivos objeto gerados a partir dos arquivos fonte
OBJECTS = $(patsubst $(MODULES_DIR)/%.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SOURCES)))

# regra padrão
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Cria diretórios se não existirem
$(BUILD_DIR):
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

# Regra para gerar os arquivos objeto
$(BUILD_DIR)/%.o: $(MODULES_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/inventory.o: $(SRC_DIR)/inventory.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)