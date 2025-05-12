# Nome do executável
EXEC = dijkstra

# Compilador e flags
CC = gcc
CFLAGS = -Wall

# Arquivos-fonte
SRCS = main.c graph.c min_heap.c dijkstra.c

# Regra principal
all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

# Limpa apenas o executável
clean:
	rm -f $(EXEC)
