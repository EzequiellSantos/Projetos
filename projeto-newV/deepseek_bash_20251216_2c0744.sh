# Crie o Makefile manualmente garantindo TABs
cat > Makefile << 'EOF'
# Makefile simplificado para Bomberman
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L -Iincludes
LDFLAGS = -lncursesw -lm

SRC_DIR = cods

# Lista específica de arquivos .c para compilar
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/mapa.c \
       $(SRC_DIR)/bomb.c \
       $(SRC_DIR)/bomb_types.c \
       $(SRC_DIR)/game_over.c \
       $(SRC_DIR)/player.c \
       $(SRC_DIR)/auth.c \
       $(SRC_DIR)/auth_menu.c \
       $(SRC_DIR)/stats.c \
       $(SRC_DIR)/database.c \
       $(SRC_DIR)/ranking.c \
       $(SRC_DIR)/bptree.c \
       $(SRC_DIR)/bptree_visual.c

OBJS = $(SRCS:.c=.o)
TARGET = jogo

# Regra padrão
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✅ Bomberman compilado com sucesso!"

# Regra genérica para compilar .c em .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET) users.db data.txt ranking_export.txt
	@echo "🧹 Arquivos removidos"

# Recompilar do zero
rebuild: clean all

# Executar
run: all
	@echo "🎮 Executando Bomberman..."
	./$(TARGET)

# Debug com valgrind
debug: all
	@echo "🐛 Executando com valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Criar arquivos necessários se não existirem
init:
	@touch users.db data.txt
	@echo "📁 Arquivos de dados criados"

# Verificação de dependências
check-deps:
	@echo "🔍 Verificando dependências..."
	@which $(CC) > /dev/null || (echo "❌ gcc não encontrado" && exit 1)
	@pkg-config --exists ncursesw || (echo "❌ ncursesw não encontrado" && exit 1)
	@echo "✅ Todas dependências encontradas"

.PHONY: all clean run debug rebuild init check-deps
EOF

# Verifique se tem TABs
cat -A Makefile | head -20