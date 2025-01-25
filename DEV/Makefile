CC = gcc
CFLAGS = -Wall -O2

all: exec/main.out exec/tst_interface.out

test: test.out

test.out: fichier_test.c 
	$(CC) $(CFLAGS) fichier_test.c -o test.out

exec/main.out: bin/traitement_images.o bin/main.o bin/analyse_couleur.o bin/utils.o
	@mkdir -p exec
	$(CC) $(CFLAGS) -o exec/main.out bin/traitement_images.o bin/utils.o bin/main.o bin/analyse_couleur.o


bin/main.o: main.c Image/traitement_images.h Couleur/analyse_couleur.h  Utils/utils.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c main.c -o bin/main.o
	
exec/tst_interface.out: bin/tst_interface.o bin/interface.o bin/config.o bin/traitement_images.o bin/analyse_couleur.o bin/utils.o
	@mkdir -p exec
	gcc -o exec/tst_interface.out bin/tst_interface.o bin/interface.o bin/config.o bin/traitement_images.o bin/analyse_couleur.o bin/utils.o

bin/traitement_images.o: Image/traitement_images.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Image/traitement_images.c -o bin/traitement_images.o

bin/utils.o: Utils/utils.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Utils/utils.c -o bin/utils.o

bin/analyse_couleur.o: Couleur/analyse_couleur.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Couleur/analyse_couleur.c -o bin/analyse_couleur.o

bin/config.o: Configuration/config.c Configuration/config.h
	@mkdir -p bin
	gcc $(CFLAGS) -c Configuration/config.c -o bin/config.o

bin/interface.o: Interface/interface.c Interface/interface.h Configuration/config.h 
	@mkdir -p bin
	gcc $(CFLAGS) -c Interface/interface.c -o bin/interface.o
	
bin/tst_interface.o: tst_interface.c Interface/interface.h Configuration/config.h Image/traitement_images.h Couleur/analyse_couleur.h  Utils/utils.h
	@mkdir -p bin
	gcc $(CFLAGS) -c tst_interface.c -o bin/tst_interface.o



clean:
	rm -rf bin exec
