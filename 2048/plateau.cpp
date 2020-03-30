#include "plateau.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Plateau::Plateau(QObject *parent) : QObject(parent) // constructeur
{
    taille = 4;
    tab = new int*[taille]; // création du tableau tab
    for (int i=0; i<taille; i++)
        tab[i] = new int[taille];
    reset_table(); // initialise à 0 toutes les valeurs de table
    score = 0;

    remplissage = 0;
    libres = taille*taille;
    cases_libres = new bool*[taille]; // création du tableau cases_libres
    for (int i=0; i<taille; i++)
        cases_libres[i] = new bool[taille];
    reset_cases_libres();
    plateau_mem = tab;
    avant_ou_apres = false;
}

Plateau::~Plateau() // destructeur
{
   free();
}


void Plateau::free()
{
    for (int i=0; i<taille; i++)
        delete [] tab[i];
    delete [] tab;
    tab = nullptr;
}

void Plateau::reset_cases_libres()
{
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++)
            cases_libres[i][j] = true;
    }
}

void Plateau::reset_table()
{
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++)
            tab[i][j] = 0;
    }
}

void Plateau::set_taille(int n)
{
    taille = n;
}





void Plateau::add_tesselle(Tesselle T) // ajouter la tesselle T au plateau
{
    //
    // ajouter EXCEPTION si cases_libres[i][j] == false //
    //
    plateau_mem = tab; // on mémorise le plateau avant de le modifier
    int i = T.GetI(); int j = T.GetJ(); // coordonnées de la tesselle
    tab[i][j] = T.GetScore();
    cases_libres[i][j] = false;
    remplissage += 1;
    libres -= 1;
    score += T.GetScore();
}

void Plateau::add_tesselle_random()
{
    int b = rand() % libres; // case libre au hazard
    int c = 0; // compteur
    int iplat; int jplat; // coordonnées de la nouvelle tesselle

    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            if (cases_libres[i][j]) { // on cherche la b ième case libre
                c += 1;
                if (c == b) {
                    iplat = i; jplat = j;
                }
            }
        }
    }

    int nombre = (rand() % 2 + 1) * 2; // nombre aléatoirement 2 ou 4
    Tesselle T( 0, nombre, 0, iplat, jplat);

    add_tesselle(T);
}








