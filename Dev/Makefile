CFLAGS = -Wall -Wextra -std=c11

# Règles pour chaque exécutable
tst_automatique.out: tst_automatique.o automatique.o config.o deplacement.o
	gcc -o tst_automatique.out tst_automatique.o automatique.o config.o deplacement.o

tst_commande_vocale.out: tst_commande_vocale.o commande_vocale.o config.o
	gcc -o tst_commande_vocale.out tst_commande_vocale.o commande_vocale.o config.o

tst_deplacement.out: tst_deplacement.o deplacement.o config.o
	gcc -o tst_deplacement.out tst_deplacement.o deplacement.o config.o

tst_image.out: tst_image.o image.o config.o
	gcc -o tst_image.out tst_image.o image.o config.o

tst_interface.out: tst_interface.o interface.o config.o
	gcc -o tst_interface.out tst_interface.o interface.o config.o

tst_config.out: tst_config.o config.o
	gcc -o tst_config.out tst_config.o config.o

tst_main.out: tst_main.o main.o config.o interface.o deplacement.o commande_vocale.o automatique.o
	gcc -o tst_main.out tst_main.o main.o config.o interface.o deplacement.o commande_vocale.o automatique.o

# Règles de compilation des fichiers sources en fichiers objets
tst_automatique.o: tst_automatique.c automatique.h config.h deplacement.h
	gcc $(CFLAGS) -c tst_automatique.c -o tst_automatique.o

tst_commande_vocale.o: tst_commande_vocale.c commande_vocale.h config.h
	gcc $(CFLAGS) -c tst_commande_vocale.c -o tst_commande_vocale.o

tst_deplacement.o: tst_deplacement.c deplacement.h config.h
	gcc $(CFLAGS) -c tst_deplacement.c -o tst_deplacement.o

tst_image.o: tst_image.c image.h config.h
	gcc $(CFLAGS) -c tst_image.c -o tst_image.o

tst_interface.o: tst_interface.c interface.h config.h
	gcc $(CFLAGS) -c tst_interface.c -o tst_interface.o

tst_config.o: tst_config.c config.h
	gcc $(CFLAGS) -c tst_config.c -o tst_config.o

tst_main.o: tst_main.c main.c config.h interface.h deplacement.h commande_vocale.h automatique.h
	gcc $(CFLAGS) -c tst_main.c -o tst_main.o

automatique.o: automatique.c automatique.h config.h
	gcc $(CFLAGS) -c automatique.c -o automatique.o

commande_vocale.o: commande_vocale.c commande_vocale.h config.h
	gcc $(CFLAGS) -c commande_vocale.c -o commande_vocale.o

config.o: config.c config.h
	gcc $(CFLAGS) -c config.c -o config.o

deplacement.o: deplacement.c deplacement.h config.h
	gcc $(CFLAGS) -c deplacement.c -o deplacement.o

image.o: image.c image.h config.h
	gcc $(CFLAGS) -c image.c -o image.o

interface.o: interface.c interface.h config.h
	gcc $(CFLAGS) -c interface.c -o interface.o

main.o: main.c config.h interface.h deplacement.h commande_vocale.h automatique.h
	gcc $(CFLAGS) -c main.c -o main.o

# Règle pour tester un exécutable
tst_automatique: tst_automatique.out
	./tst_automatique.out

tst_commande_vocale: tst_commande_vocale.out
	./tst_commande_vocale.out

tst_config: tst_config.out
	./tst_config.out

tst_deplacement: tst_deplacement.out
	./tst_deplacement.out

tst_image: tst_image.out
	./tst_image.out

tst_interface: tst_interface.out
	./tst_interface.out

tst_main: tst_main.out
	./tst_main.out
# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf *.o *.out
