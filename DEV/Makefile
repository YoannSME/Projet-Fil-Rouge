CC = gcc
CFLAGS = -Wall -O3

all: exec/tst_interface.out
	
exec/tst_interface.out: bin/tst_interface.o bin/interface.o bin/config.o bin/traitement_images.o bin/analyse_couleur.o bin/utils.o bin/traitement_vocal.o
	@mkdir -p exec
	$(CC) $(CFLAGS) -o exec/tst_interface.out bin/tst_interface.o bin/interface.o bin/config.o bin/traitement_images.o bin/analyse_couleur.o bin/utils.o bin/traitement_vocal.o

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
	$(CC) $(CFLAGS) -c Configuration/config.c -o bin/config.o

bin/interface.o: Interface/interface.c Interface/interface.h Configuration/config.h Commande_vocale/traitement_vocal.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Interface/interface.c -o bin/interface.o

bin/tst_interface.o: tst_interface.c Interface/interface.h Configuration/config.h Image/traitement_images.h Couleur/analyse_couleur.h Utils/utils.h Commande_vocale/traitement_vocal.h
	@mkdir -p bin
	$(CC) $(CFLAGS) -c tst_interface.c -o bin/tst_interface.o

bin/traitement_vocal.o: Commande_vocale/traitement_vocal.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c Commande_vocale/traitement_vocal.c -o bin/traitement_vocal.o



doc: documentation/Doxyfile
	@echo "Génération de la documentation avec Doxygen..."
	@doxygen documentation/Doxyfile

documentation/Doxyfile:
	@echo "Création du fichier de configuration Doxyfile..."
	@mkdir -p documentation
	@doxygen -g documentation/Doxyfile
	@sed -i 's|^OUTPUT_DIRECTORY.*|OUTPUT_DIRECTORY = documentation|' documentation/Doxyfile
	@sed -i 's|^INPUT.*|INPUT = Configuration Couleur Image Interface Commande_vocale|' documentation/Doxyfile
	@sed -i 's|^FILE_PATTERNS.*|FILE_PATTERNS = *.h *.c|' documentation/Doxyfile
	@sed -i 's|^GENERATE_HTML.*|GENERATE_HTML = YES|' documentation/Doxyfile
	@sed -i 's|^GENERATE_LATEX.*|GENERATE_LATEX = YES|' documentation/Doxyfile
	@echo "Doxyfile créé et configuré pour la documentation."

clean_doc:
	rm -rf documentation/html documentation/latex documentation/refman.pdf



clean:
	rm -rf bin exec documentation Doxyfile
