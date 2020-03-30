#include "plateau.h"
#include <iostream>
using namespace std;

Plateau::Plateau(QObject *parent) : QObject(parent)
{
    taille = 4;
    tab = new int*[taille]; // création du tableau
    for (int i=0; i<taille; i++) {
        tab[i] = new int[taille];
    }
    reset_table(); // initialise à 0 toutes les valeurs de table
}




