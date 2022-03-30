#2 listes de directories, un pour préciser les fichiers sources et un autre pour les includes
#CODEDIRS=. lib
INCDIRS=. ./include/

#surnom du compilateur, ça à l'air d'être une norme
CC=gcc
#Flags de warning suplementaire, surement utile pour nous
WFLAGS=-Wall -Wextra
#Flags permettant a make de trouver automatiquement les includes sans devoir les ajouter a la compilation des .o
DEPFLAGS=-MP -MD

#Pour mettre tout les drapeaux et ainsi eviter la redondance, le foreach permet d'ajouter un -I donc include a tout les
#directory qu'on aura listé dans INCDIRS, . étant le directory actuel 
ALLFLAGS=$(WFLAGS) $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)


ENS=lib/ensemble.o

LIBS=lib/*.c
CACIEN=Ancien/*.c

MAINS=*.c
EVERYC=$(LIBS) $(MAINS) $(CACIEN)

#Dit que les fichiers sources sont tous les .c dans . et ./include/

#Les fichier objets pour faire les executables, 2 manières
OBJECTS=$(LIBS:.c=.o)
TOBJECTS=$(EVERYC:.c=.o)
#1ère avec ces listes là honnêtement, pas utile d'aller plus loin, mais on peut aussi faire
#OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

#Les .d permettant à make d'inclure les includes directement
DEPFILES=$(EVERYC:.c=.d)
#Les headers, pas besoin si utilisation des outils de make spécifique aux headers
#HEADERS=$(SOURCES:.c=.h)

#Les différents executables dans le futur n'aura que main
EXECUTABLES=pgi testSaturation testParseur ancienParseur ancienSaturation
#testMultiplication testSoustraction

#Si je veux tout build, il me faut tout ces fichiers, on la met en 1er parce que 'make' tout court prend la 1ère instruction
all: $(EXECUTABLES)

pgi: $(OBJECTS)
	$(CC) -o $@ $^ 

testSaturation: testSaturation.o lib/saturation.o $(ENS)
	$(CC) -o $@ $^

testParseur: testParseur.o lib/parseur.o $(ENS)
	$(CC) -o $@ $^

ancienParseur:Ancien/ancienParseur.o $(ENS)
	$(CC) -o $@ $^

ancienSaturation:Ancien/ancienSaturation.o $(ENS)
	$(CC) -o $@ $^

#Il y a du regex en makefile les wildcard : % , le $@ signifie ce qu'on veut créer pour pas se repeter et le $< c'est pour ajouter tout ce dont le .o dépend, donc le .c et les .h
%.o: %.c
	$(CC) $(ALLFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXECUTABLES) $(TOBJECTS) $(DEPFILES)