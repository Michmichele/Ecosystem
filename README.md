# Ecosystem

#Sujet du projet
L’objectif de ce sujet est la réalisation d’un projet de programmation d’un écosystème virtuel utilisant des listes chaînées.
Le modele d’écosystème que vous allez programmer n’a aucune prétention à être réaliste, mais il permet de se familiariser avec le concept d’équilibre, primordial dans un écosystème.
Cet écosystème contiendra deux types d’entités virtuelles : des proies et des predateurs, susceptibles de manger les proies.
Votre écosystème est un monde discret (un tore, que nous afficherons comme un rectangle) contenant un certain nombre de cases, identifiées par leurs coordonnées
(entieres) x et y. Chaque proie (et chaque prédateur) est dans une case donnée et peut se déplacer.
A un instant donnée, une case peut contenir plusieurs proies et plusieurs prédateurs. Chaque case peut aussi contenir de l’herbe, la nourriture des proies.
Les données utilisées pour la simulation sont une liste chaînée contenant les proies et une autre liste chaînée contenant les prédateurs ainsi qu’un tableau statique a deux dimensions représentant le monde.

#Contenu du programme
— main_tests.c, contient un main avec les tests des fonctions,
— main_ecosys.c, contient un main permettant de simuler l'écosystème,
— ecosys.c, contient toutes les autres fonctions de manipulation de listes.
— ecosys.h, contient les prototypes des fonctions de ecosys.c et les définitions de structure (.h).

Le Makefile permet de compiler le programme.
