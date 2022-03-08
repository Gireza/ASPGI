# -*- MakeFile -*-

#Va compiler pour faire parseur PGI et ranTabGen
#

all: parseur PGI rankTabGen

parseur: parseur.o
	gcc parseur.o -o parseur -lm

parseur.o: parseur.c
	gcc -c parseur.c

rankTabGen: rankTabGen.o
	gcc rankTabGen.o -o rankTabGen -lm

rankTabGen.o: rankTabGen.c
	gcc -c rankTabGen.c

PGI: PGI.o utile.o
	gcc PGI.o utile.o -o PGI -lm

PGI.o: PGI.c utile.h
	gcc -c PGI.c

utile.o: utile.c
	gcc -c utile.c

clean:
	rm *.o parseur rankTabGen PGI