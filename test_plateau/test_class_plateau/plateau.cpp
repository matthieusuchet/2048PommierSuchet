#include "plateau.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


Plateau::Plateau()    // QObject *parent) : QObject(parent) // constructeur
{
    taille = 4;
    score = 0;
    remplissage = 0;
    libres = taille*taille;

    tab = new int*[taille]; // création du tableau tab
    cases_libres = new bool*[taille]; // création du tableau cases_libres
    for (int i=0; i<taille; i++) {
        tab[i] = new int[taille];
        cases_libres[i] = new bool[taille];
    }

    reset_table(); // initialisation de tab et cases_libres

    plateau_mem = tab;
    avant_ou_apres = false;

    srand (time(NULL));
}

Plateau::~Plateau() // destructeur
{
   free();
}

void Plateau::free()
{
    for (int i=0; i<taille; i++) {
        delete [] tab[i];
        delete [] cases_libres[i];
    }
    delete [] tab;
    delete [] cases_libres;
    tab = nullptr;
    cases_libres = nullptr;
}


bool Plateau::est_plein()
{
    return (libres == 0);
}

bool Plateau::est_vide()
{
    return (remplissage == 0);
}

void Plateau::reset_table()
{
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            tab[i][j] = 0;
            cases_libres[i][j] = true;
        }
    };
    remplissage = 0;
    libres = taille*taille;
    score = 0;
}

int Plateau::get_score()
{
    return score;
}

void Plateau::set_taille(int n)
{
    taille = n;
}

void Plateau::add_tesselle(Tesselle T) // ajouter la tesselle T au plateau
{
    //
    // ajouter EXCEPTION si (cases_libres[i][j] == false) //
    //
    plateau_mem = tab;                  // on mémorise le plateau avant de le modifier
    int i = T.GetI(); int j = T.GetJ(); // coordonnées de la tesselle
    tab[i][j] = T.GetScore();
    cases_libres[i][j] = false;
    remplissage += 1;
    libres -= 1;
    score += T.GetScore();
}

void Plateau::add_tesselle_random()
{
    //
    // ajouter EXCEPTION si (libres == 0) //
    //
    int b = rand() % libres; // case libre au hazard
    int c = 0;               // compteur
    int iplat; int jplat;    // coordonnées de la nouvelle tesselle

    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            if (cases_libres[i][j]) { // on cherche la b-ième case libre
                if (c == b) {
                    iplat = i; jplat = j;
                }
                c += 1;
            }
        }
    }

    int ident = 0;
    int nombre = (rand() % 2 + 1) * 2; // nombre aléatoirement 2 ou 4
    int couleur = 0;
    Tesselle T( ident, nombre, couleur, iplat, jplat);

    add_tesselle(T);
}

void Plateau::init()
{
    reset_table();
    int une_ou_deux_tesselles = (rand() % 2); // nombre aléatoirement 0 ou 1
    add_tesselle_random();
    if (une_ou_deux_tesselles) {
        add_tesselle_random();
    }
}







void Plateau::Print() {
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}




