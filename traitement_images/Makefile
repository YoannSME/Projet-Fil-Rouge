all: exec/main.out

test: test.out

test.out: fichier_test.c 
	gcc -Wall fichier_test.c -o test.out

bin/main.o: main.c traitement_images.h
	@mkdir -p bin
	gcc -g -c main.c -o bin/main.o -W -Wall

bin/traitement_images.o: traitement_images.c
	@mkdir -p bin
	gcc -g -c traitement_images.c -o bin/traitement_images.o -W -Wall

exec/main.out: bin/traitement_images.o bin/main.o
	@mkdir -p exec
	gcc -g -o exec/main.out bin/traitement_images.o bin/main.o

clean:
	rm -rf bin exec
