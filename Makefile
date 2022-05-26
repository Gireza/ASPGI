CC=gcc
CFLAGS=-W -Wall -std=c11
LDFLAGS=
EXEC=pgi
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
	
pgi: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o resultat.txt

mrproper: clean
	@rm -rf $(EXEC)
