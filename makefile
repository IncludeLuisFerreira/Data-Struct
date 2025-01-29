CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -Iinclude
SRC = src/*.c
APP = app/*.c

# Regra principal
all:
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(APP) -o output

# Limpeza
clean:
	@rm -rf *.o output
