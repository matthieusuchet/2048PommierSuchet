#include "plateau.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


Plateau::Plateau()
{
    reset_table();
    srand (time(NULL));
}

ostream& operator<<(ostream &sortie, Plateau &p) {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
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

void Plateau::reset_table() // initialisation de tab, cases_libres et plateau_mem
{
    Tesselle T_init(0,0,0,0,0);
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab[i][j] = T_init;
            cases_libres[i][j] = true;
        }
    }
    copie_tab_mem(); avant_ou_apres = false;
    score = 0;
    remplissage = 0; libres = 16;
    add_tesselle_random(); add_tesselle_random(); // 2 tesselles pour commencer
}

int Plateau::get_score()
{
    return score;
}

void Plateau::add_tesselle(Tesselle T) // ajouter la tesselle T au plateau
{
    //
    // ajouter EXCEPTION si (cases_libres[i][j] == false) //
    //
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

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j]) { // on cherche la b-ième case libre
                if (c == b)
                    {iplat = i; jplat = j;}
                c += 1;
            }
        }
    }

    int ident = 0; int nombre = 2;
    int proba = rand() % 5; // 1 chance sur 5 d'avoir un 4, sinon un 2
    if (proba == 0) {nombre = 4;}
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
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab_mem[i][j] = tab[i][j];
            cases_libres_mem[i][j] = cases_libres[i][j];
        }
    }
}


void Plateau::deplacement(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new)
{
    //
    // ajouter EXCEPTION si ( cases_libres[x][y] = false ) //
    //
    Tesselle T_new = vect_tess[x_old];
    T_new.SetPosition(T_new.GetI(),x_new);
    vect_tess[x_new] = T_new;

    vect_libres[x_old] = true;
    vect_libres[x_new] = false;
}

void Plateau::fusion(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new)
{
    //
    // ajouter EXCEPTION si ( pas fusionnables ) //
    //
    Tesselle T_old = vect_tess[x_old];
    Tesselle* T_new = &vect_tess[x_new];
    T_new->Fusion(T_old);

    vect_libres[x_old] = true;
    vect_libres[x_new] = false;

    remplissage --; libres ++;
}

bool Plateau::gauche_ligne(Tesselle* vect_tess, bool* vect_libres)
// réalise un coup vers la gauche dans vect_libres (vecteur de 4 tesselles) suivant les règles du 2048
// vect_libres est le vecteur booléen de présence associé à vect_tess
{
    bool a_bouge = false; // vérifie si au moins un mouvent a été fait
    bool deja_fusionne [4] = {false, false, false, false}; // verifie si une case a déjà fusionné pour pas qu'elle fusionne 2 fois
    for (int j=1; j<4; j++) { // on saute la tesselle la plus à gauche (j=0) qui ne bougera pas de toute façon

        if (vect_libres[j] == false) { // s'il y a une tesselle en indice j à considérer

            int j_avant = j; // indice de la derniere case vide à gauche
            while ((j_avant>=1) && (vect_libres[j_avant-1] == true))
                j_avant --;

            if (j_avant>0) { // s'il y a une autre tesselle à gauche
                if (vect_tess[j].GetScore() == vect_tess[j_avant-1].GetScore()) { // s'il peut y avoir fusion
                    if (! deja_fusionne[j_avant-1]) { // si cette case n'a pas déjà fusionné
                        fusion(&vect_tess[0], &vect_libres[0],j,j_avant-1);
                        deja_fusionne[j_avant-1] = true;
                        a_bouge = true;
                    }
                    else // si la case a déjà fusionné, elle ne doit pas fusionner 2 fois
                        {deplacement(&vect_tess[0], &vect_libres[0],j,j_avant); a_bouge = true;}
                }
                else // si les nombres ne sont pas identiques, il n'y a pas fusion
                    {deplacement(&vect_tess[0], &vect_libres[0],j,j_avant); a_bouge = true;}
            }

            else // s'il n'y a pas de tesselle à gauche
                {deplacement(&vect_tess[0], &vect_libres[0],j,0); a_bouge = true;} // déplacement jusqu'à l'indice 0
        }
    }
    return a_bouge;
}


bool Plateau::move(int dir)
{
    copie_tab_mem();      // on mémorise le plateau avant de le modifier
    bool a_bouge = false; // vérifie si au moins un mouvent a été fait
    
    for (int n=0; n<4; n++) { // parcours des lignes ou colonnes selon la direction
        // on met toutes les tesselles de chaque ligne ou colonne dans vect_tess de gauche à droite
        // en sorte qu'un coup dans n'importe quelle direction revienne à un coup vers la gauche dans vect_tess
        Tesselle vect_tess[4];
        bool vect_libres[4];
        for (int k=0; k<4; k++) { // parcours des cases de chaque ligne ou colonne
            if (dir == 1) // gauche
                {vect_tess[k] = tab[n][k]; vect_libres[k] = cases_libres[n][k];}
            if (dir == 2) //droite
                {vect_tess[k] = tab[n][4-k-1]; vect_libres[k] = cases_libres[n][4-k-1];}
            if (dir == 3) // haut
                {vect_tess[k] = tab[k][n]; vect_libres[k] = cases_libres[k][n];}
            if (dir == 4) // bas
                {vect_tess[k] = tab[4-k-1][n]; vect_libres[k] = cases_libres[4-k-1][n];}
        }

        a_bouge = gauche_ligne(&vect_tess[0], &vect_libres[0]) || a_bouge; // coup vers la gauche dans vect_tess

        // mise à jour tab et cases_libres à partir de vect_tess et vect_libres
        for (int k=0; k<4; k++) {
            if (dir == 1) // gauche
                {tab[n][k]= vect_tess[k]; cases_libres[n][k] = vect_libres[k];}
            if (dir == 2) // droite
                {tab[n][4-k-1] = vect_tess[k]; cases_libres[n][4-k-1] = vect_libres[k];}
            if (dir == 3) // haut
                {tab[k][n] = vect_tess[k]; cases_libres[k][n] = vect_libres[k];}
            if (dir == 4) // bas
                {tab[4-k-1][n] = vect_tess[k]; cases_libres[4-k-1][n] = vect_libres[k];}
        }
    }

    if (a_bouge)
        add_tesselle_random();

    return a_bouge;
}





