#include "plateau.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <QColor>
using namespace std;


Plateau::Plateau(QObject *parent) : QObject(parent)
{
    init();
    best_score = 0;
    srand (time(NULL));
    numMove=0;
    //plateauMoved();
    //couleurs = {"#edebe7", "#d4cdb4"};
    //cout << couleurs[0] << couleurs[1] << endl;
}

void Plateau::init() // initialisation des variables pour un début de partie
{
    if (score > best_score) // mise à jour du meilleur score
        best_score = score;

    Tesselle T_init(0,0,0,0);
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab[i][j] = T_init;
            cases_libres[i][j] = true;
        }
    }
    copie_tab_mem(); a_deja_undo = false;
    score = 0; libres = 16;
    add_tesselle_random(); add_tesselle_random(); // 2 tesselles pour commencer
}


// /////////////////////////////
// affichage QML ///////////////
// /////////////////////////////

QList<QString> Plateau::readMove(){
    QList<QString> listNombres;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false)
                listNombres.append(QString::number(tab[i][j].GetScore()));
            else
                listNombres.append(QString::number(0));
        }
    }
    return listNombres;
}

QList<bool> Plateau::readVisible(){
    QList<bool> visibles;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false)
                visibles.append(true);
            else
                visibles.append(false);
        }
    }
    return visibles;
}

QList<QString> Plateau::readCouleur()
{
    QList<QString> listCouleurs;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            listCouleurs.append(tab[i][j].GetCouleur());
        }
    }
    return listCouleurs;
}

QList<QString> Plateau::readCoulText()
{
    QList<QString> listCouleurs;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            listCouleurs.append(tab[i][j].GetCoulText());
        }
    }
    return listCouleurs;
}

QList<QString> Plateau::readScores()
{
    QList<QString> scores;
    scores.append(QString::number(score));      // score courant
    scores.append(QString::number(best_score)); // meilleur score
    return scores;
}


QString Plateau::readTest()
{
    if (test == 1)
        return "#89817a";
    else
        return "#aaaaaa";
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


// /////////////////////////////
// ajout des tesselles /////////
// /////////////////////////////

void Plateau::add_tesselle(Tesselle T) // ajouter la tesselle T au plateau
{
    //
    // ajouter EXCEPTION si (cases_libres[i][j] == false) //
    //
    int i = T.GetI(); int j = T.GetJ(); // coordonnées de la tesselle
    tab[i][j] = T;
    cases_libres[i][j] = false;
    libres --;
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

    int nombre = 2; int indice_couleur = 0;
    int proba = rand() % 5; // 1 chance sur 5 d'avoir un 4, sinon un 2
    if (proba == 0) {nombre = 4; indice_couleur = 1;}
    Tesselle T( nombre, indice_couleur, iplat, jplat);

    add_tesselle(T);

    if (a_perdu()) {
        test = 2;
        peutetrefin();

        init();
        plateauMoved();
        //
        //
        // faire quelque chose si c'est perdu -> fin de partie //
        //
        //
    }

}


// /////////////////////////////
// déplacements des tesselles //
// /////////////////////////////

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
    Tesselle* T_new = &vect_tess[x_new];
    T_new->Fusion();

    vect_libres[x_old] = true;
    vect_libres[x_new] = false;

    score += T_new->GetScore();
    libres ++;
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
                    else { // si la case a déjà fusionné, elle ne doit pas fusionner 2 fois
                        if (j!=j_avant) // déplacement vers j_avant si c'est une case différente de la case actuelle
                            {deplacement(&vect_tess[0], &vect_libres[0],j,j_avant); a_bouge = true;}
                    }
                }
                else {// si les nombres ne sont pas identiques, il n'y a pas fusion
                    if (j!=j_avant) // déplacement vers j_avant si c'est une case différente de la case actuelle
                        {deplacement(&vect_tess[0], &vect_libres[0],j,j_avant); a_bouge = true;}
                }
            }

            else // s'il n'y a pas de tesselle à gauche
                {deplacement(&vect_tess[0], &vect_libres[0],j,0); a_bouge = true;} // déplacement jusqu'à l'indice 0
        }
    }
    return a_bouge;
}


void Plateau::move(int dir)
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

    plateauMoved();
}


// /////////////////////////////
// gestion fin de partie ///////
// /////////////////////////////

bool Plateau::possible_move(int dir) // est ce qu'un déplacement dans cette direction conduit à une modification du plateau
{
    for (int n=0; n<4; n++) { // parcours des lignes ou colonnes selon la direction
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

        for (int j=1; j<4; j++) {
            if (vect_libres[j] == false) {

                int j_avant = j; // indice de la derniere case vide à gauche
                while ((j_avant>=1) && (vect_libres[j_avant-1] == true))
                    j_avant --;

                if (j_avant>0) { // s'il y a une autre tesselle à gauche
                    if (vect_tess[j].GetScore() == vect_tess[j_avant-1].GetScore()) // s'il peut y avoir fusion
                        return true;
                    if (j_avant != j) // s'il y a déplacement
                        return true;
                }

                if (j_avant==0) // s'il n'y a pas de tesselle à gauche et ya déplacement
                    return true; // déplacement jusqu'à l'indice 0
            }
        }
    }
    return false;
}

bool Plateau::a_perdu()
{
    if (libres == 0) {
        bool peut_bouger = false;
        peut_bouger = possible_move(1) || possible_move(2) || possible_move(3) || possible_move(4);
        return (! peut_bouger);
    }
    return false;
}

// /////////////////////////////
// gestion option pédagogique //
// /////////////////////////////

void Plateau::copie_tab_mem()
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab_mem[i][j] = tab[i][j];
            cases_libres_mem[i][j] = cases_libres[i][j];
        }
    }
}

void Plateau::echanger_mem()
{
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            // échanger les valeurs de tab et de tab_mem
            Tesselle tab_aux = tab[i][j];
            tab[i][j] = tab_mem[i][j];
            tab_mem[i][j] = tab_aux;
            // idem pour cases_libres et cases_libres_mem
            bool case_aux = cases_libres[i][j];
            cases_libres[i][j] = cases_libres_mem[i][j];
            cases_libres_mem[i][j] = case_aux;
        }
    }
}

void Plateau::mise_a_jour_score()
{
    score = 0;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (! cases_libres[i][j])
                score += tab[i][j].GetScore();
        }
    }
}

void Plateau::undo()
{
    if (! a_deja_undo) { // si le joueur n'est pas déjà revenu en arrière
        echanger_mem();
        a_deja_undo = true;
        mise_a_jour_score();
    }
}

void Plateau::redo()
{
    if (a_deja_undo) { // si c'est bien après un retour en arrière
        echanger_mem();
        a_deja_undo = false;
        mise_a_jour_score();
    }
}

///////////////////////////
/// interaction avec QML //
///////////////////////////
/*
void Plateau::print(int num){
   // cout << "moved" << endl;
    numMove = num;
  //  cout << numMove << endl;
  //  plateauMoved();
    cout << *this << endl;
    plateauMoved();
}

QList<QString> Plateau::readMove(){
    QList<QString> listNombres;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false)
                listNombres.append(QString::number(tab[i][j].GetScore()));
            else
                listNombres.append(QString::number(0));
        }
    }
    return listNombres;
}

QList<bool> Plateau::readVisible(){
    QList<bool> visibles;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false)
                visibles.append(true);
            else
                visibles.append(false);
        }
    }
    return visibles;
}

QList<QString> Plateau::readCouleurs(){
    QList<QString> couleurs_tesselles;
    int coul;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false){
                coul = log2(tab[i][j].GetScore())-1;
                couleurs_tesselles.append(couleurs[coul]);
            }
            else{
                couleurs_tesselles.append(couleurs[0]);
            }
        }
    }
    return couleurs_tesselles;
}
*/
