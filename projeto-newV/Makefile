# Makefile simplificado para Bomberman
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lncursesw

SRC_DIR = cods
INCLUDE_DIR = includes

# Todos os arquivos .c na pasta cods
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
TARGET = jogo

# Regra padrão
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Bomberman compilado com sucesso!"

# Regra genérica para compilar .c em .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET) users.db data.txt
	@echo "🧹 Arquivos removidos"

run: all
	@echo "🎮 Executando Bomberman..."
	./$(TARGET)

.PHONY: all clean run