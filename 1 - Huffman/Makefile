# Nome do executável
EXEC = huffman

# Diretório dos arquivos fonte
SRC_DIR = .

# Fontes e cabeçalhos
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/compress.c \
      $(SRC_DIR)/decompress.c \
      $(SRC_DIR)/huffman_tree.c \
      $(SRC_DIR)/min_heap.c \
      $(SRC_DIR)/bit_reader.c \
      $(SRC_DIR)/bit_writer.c \
      $(SRC_DIR)/utils.c

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Regra padrão
all: $(EXEC)

# Compilação do executável
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Limpeza
clean:
	rm -f $(EXEC)

# PHONY evita conflitos com arquivos chamados "all" ou "clean"
.PHONY: all clean
