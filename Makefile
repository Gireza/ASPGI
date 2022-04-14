CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c11
LDFLAGS=
EXEC=pgi
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

pgi: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: hello.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
