#include "plateau.h"
#include <iostream>
using namespace std;

Plateau::Plateau(int n)
{
    taille = n;
    table = new int*[taille]; // création du tableau
    for (int i=0; i<n; i++) {
        table[i] = new int[n];
    }
    reset_table(); // initialise à 0 toutes les valeurs de table
}
