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
    reset_table();
    srand (time(NULL));
}

ostream& operator<<(ostream &sortie, Plateau &p) {  // opérateur <<
    for (int i=0; i<p.taille; i++) {
        for (int j=0; j<p.taille; j++) {
            if (p.cases_libres[i][j] == false)
                sortie << p.tab[i][j] << " ";
            else
                sortie << 0 << " ";
        }
        sortie << endl;
    };
    return sortie;
}


bool Plateau::est_plein()
{
    return (libres == 0);
}

bool Plateau::est_vide()
{
    return (remplissage == 0);
}

void Plateau::reset_table() // initialisation de tab, cases_libres et plateau_mem
{
    Tesselle T_init(0,0,0,0,0);
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            tab[i][j] = T_init;
            cases_libres[i][j] = true;
        }
    }
    copie_tab_mem();
    score = 0;
    remplissage = 0;
    libres = taille*taille;
    avant_ou_apres = false;
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

    copie_tab_mem();                // on mémorise le plateau avant de le modifier
    int i = T.GetI(); int j = T.GetJ(); // coordonnées de la tesselle
    tab[i][j] = T;
    cases_libres[i][j] = false;
    remplissage ++; libres --;
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

void Plateau::copie_tab_mem()
{
    for (int i=0; i<taille; i++) {
        for (int j=0; j<taille; j++) {
            tab_mem[i][j] = tab[i][j];
            cases_libres_mem[i][j] = cases_libres[i][j];
        }
    }
}


void Plateau::deplacement(int i,int j,int x, int y)
{
    //
    // ajouter EXCEPTION si ( cases_libres[x][y] = false ) //
    //
    tab[x][y] = tab[i][j];
    cases_libres[i][j] = true;
    cases_libres[x][y] = false;
}


void Plateau::gauche(int i) // gauche_ligne
{
    for (int j=1; j<taille; j++) { // on saute la tesselle la plus à gauche (j=0) qui ne bougera pas
        if (cases_libres[i][j] == false) { // si il y a une tesselle en (i,j)

            int j_avant = j; // indice de la derniere case vide à gauche
            while ((j_avant>=1) && (cases_libres[i][j_avant-1] == true))
                j_avant --;

            if ((j_avant>0) && (j_avant!=j)) { // s'il y a une autre tesselle à gauche
                if (tab[i][j].GetScore() == tab[i][j_avant-1].GetScore()) // s'il peut y avoir fusion
                    fusion(i,j_avant-1,i,j,i,j_avant-1);
                else
                    deplacement(i,j,i,j_avant);
            }

            else
                deplacement(i,j,i,j_avant);
        }
    }
}



void Plateau::fusion(int i1, int j1, int i2, int j2, int x, int y)
{
    //
    // ajouter EXCEPTION si ( pas fusionnables ) //
    //
    cases_libres[i1][j1] = true;
    cases_libres[i2][j2] = true;
    Tesselle T_fusion(0, 2*((tab[i1][j1]).GetScore()),0,x,y);
    tab[x][y] = T_fusion;
    cases_libres[x][y] = false;
}




