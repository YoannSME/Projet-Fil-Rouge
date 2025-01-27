import os
import time
import turtle
import re

def process_file(filename):
    """Lit et exécute les commandes Turtle depuis un fichier."""
    with open(filename, 'r') as file:
        lines = file.readlines()

    for line in lines:
        line = line.strip()
        # Traite les commandes Turtle
        if match := re.match(r"forward\((\d+)\)", line):
            value = int(match.group(1))
            turtle.forward(value)
        elif match := re.match(r"backward\((\d+)\)", line):
            value = int(match.group(1))
            turtle.backward(value)
        elif match := re.match(r"turn\((\d+)\)", line):
            value = int(match.group(1))
            turtle.right(value)
            
    file.close()
    # Supprime le fichier après traitement
    os.remove(filename)
def main():
    """Boucle principale qui surveille les fichiers dans le répertoire courant."""
    turtle.speed(1)  # Réglage de la vitesse de la tortue
    os.getcwd()
    file = os.getcwd() 
    file += "/commande/transcription.txt"
    while True:
        try:
            process_file(file)
        except Exception as e:
            print(f"Erreur lors du traitement de {file}: {e}")
            time.sleep(0.5)

if __name__ == "__main__":
    main()