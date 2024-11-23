all: exec/sortie.out

bin/sortie.o: sortie.c traitement_images.h
	@mkdir -p bin
	gcc -c sortie.c -o bin/sortie.o -W -Wall

bin/traitement_images.o: traitement_images.c
	@mkdir -p bin
	gcc -c traitement_images.c -o bin/traitement_images.o -W -Wall

exec/sortie.out: bin/traitement_images.o bin/sortie.o
	@mkdir -p exec
	gcc -o exec/sortie.out bin/traitement_images.o bin/sortie.o

clean:
	rm -rf bin exec
