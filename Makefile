# Makefile - build Sim Seiei  (Windows + MinGW / MSYS2)

CC      = gcc
CFLAGS  = -g3 -O0 -Wall
LDFLAGS = -lgdi32
SRC     = $(wildcard src/*.c)
OUT     = bin/simseiei.exe

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	rm -rf bin
