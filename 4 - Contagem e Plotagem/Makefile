# Compilador
CC = gcc
# Flags de compilação
CFLAGS = -Wall -Wextra -Iinclude -g
# Nome do executável
TARGET = pq

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include

# Arquivos fonte (na ordem correta de dependência)
SRCS = $(SRC_DIR)/priority_list_unsorted.c \
       $(SRC_DIR)/priority_heap.c \
       $(SRC_DIR)/metrics.c \
       $(SRC_DIR)/main.c

# Regra principal - compila tudo de uma vez
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run