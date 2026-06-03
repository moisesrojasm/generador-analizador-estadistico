CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm

SRC = src/main.c src/generacion.c src/ordenamiento.c src/estadistica.c
OBJ = build/main.o build/generacion.o build/ordenamiento.o build/estadistica.o
EXEC = bin/practica2

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o bin/*