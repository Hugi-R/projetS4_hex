#!/bin/sh
#commande pour lancer Hex en cherchant les bibliothèques dans le répertoire courrant.
cd obj/
java -Djava.library.path=.. Hex
