CC = gcc
CFLAGS = -Wall -O2

all: exec/main.out

test: test.out

test.out: fichier_test.c 
	gcc -Wall fichier_test.c -o test.out

bin/main.o: main.c Image/traitement_images.h Couleur/analyse_couleur.h  Utils/utils.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c main.c -o bin/main.o
	

bin/traitement_images.o: Image/traitement_images.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Image/traitement_images.c -o bin/traitement_images.o

bin/utils.o: Utils/utils.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Utils/utils.c -o bin/utils.o

bin/analyse_couleur.o: Couleur/analyse_couleur.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Couleur/analyse_couleur.c -o bin/analyse_couleur.o



exec/main.out: bin/traitement_images.o bin/main.o bin/analyse_couleur.o bin/utils.o
	@mkdir -p exec
	$(CC) $(CFLAGS) -o exec/main.out bin/traitement_images.o bin/utils.o bin/main.o bin/analyse_couleur.o

clean:
	rm -rf bin exec
