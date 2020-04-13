# 2048PommierSuchet

Projet d'application graphique en Qt Qml et C++

Jeu : 2048

Cette application permet de jouer au jeu du 2048.
Ce jeu se joue avec les touches fléchées du clavier. 
L'objectif est d'atteindre le nombre 2048 en combinant des tesselles mobiles deux à deux.
Lorsque cet objectif est atteint, il est possible de continuer à jouer pour améliorer son score.

Ce jeu est personnalisable à l'aide d'un menu.
Il est possible de changer la base utilisée pour les calculs, qui est 2 par défaut.
Il est également possible de changer le jeu de couleurs des tesselles.

Des raccoucis claviers sont disponibles (testés sous Windows):
Ctrl+Z -> retour arrière
Ctrl+Y -> retour avant
Ctrl+N -> nouvelle partie
Escape -> quitter l'application

Lors de la fermeture de l'application la partie en cours est sauvegardée dans un fichier local .dat.
Cette partie, si elle existe, est rechargée lors du lancement suivant de l'application.

Un fichier excel est joint au projet.
Il contient le cahier des charges ainsi que la description des différents
éléments de de code nécessaires à l'application graphique tels qu'ils ont été initialement pensés.
La description faite par ce fichier n'est pas à jour. 
Toutefois le code est largement commenté pour aider à sa compréhension.
De plus les fichiers headers permettent de synthétiser les caractéristiques des classes Plateau et Tesselle.
