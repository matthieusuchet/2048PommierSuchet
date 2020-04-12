#include "plateau.h"
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

using namespace std;


Plateau::Plateau(QObject *parent) : QObject(parent)
{
    base = 2;
    jeuDeCouleurs = 1;
    init();
    best_score = 0;
    srand (time(NULL));
}

void Plateau::init() // initialisation des variables pour un début de partie
{

    if (score > best_score) // mise à jour du meilleur score
        best_score = score;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab[i][j].SetExp(1);
            cases_libres[i][j] = true;
        }
    }
    score = 0; libres = 16;
    add_tesselle_random(); add_tesselle_random(); // 2 tesselles pour commencer
    copie_tab_mem(); a_deja_undo = false; score_mem = 0;
    gagne = false;

    // signaux pour QML
    partieDebOuFin();
    plateauMoved();
}



// /////////////////////////////
// interaction QML /////////////
// /////////////////////////////

QList<QString> Plateau::readMove(){
    QList<QString> listNombres;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j] == false)
                listNombres.append(QString::number(tab[i][j].GetScore(base)));
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
            int ind = tab[i][j].GetIndCouleur();
            switch(jeuDeCouleurs){
                case 1:
                    listCouleurs.append(liste_coul[ind]);
                    break;
                case 2:
                    listCouleurs.append(liste_coul_bleu[ind]);
                    break;
                case 3:
                    listCouleurs.append(liste_coul_vert[ind]);
                    break;
            }
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



QList<bool> Plateau::readFinPartie(){
    QList<bool> ls_visibleGP;  // visible true/false
                               //pour calque gagné/perdu (dans cet ordre)
    if(score){
        if(gagne){
            ls_visibleGP.append(true);
            ls_visibleGP.append(false);
        }else{
            ls_visibleGP.append(false);
            ls_visibleGP.append(true);
        }
    }else{      // score=0 -> début de partie
        ls_visibleGP.append(false);
        ls_visibleGP.append(false);
    }
    return ls_visibleGP;
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

void Plateau::add_tesselle(int exp, int i, int j) // ajouter une tesselle au plateau
{
    //
    // ajouter EXCEPTION si (cases_libres[i][j] == false) //
    //
    tab[i][j].SetExp(exp);
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
    int exp = 1;
    int proba = rand() % 5; // 1 chance sur 5 d'avoir un 4, sinon un 2
    if (proba == 0) {exp = 2;}

    add_tesselle(exp,iplat,jplat);

    if (a_perdu()) {
        partieDebOuFin();

        /*

         faire quelque chose si c'est perdu -> fin de partie //

        */

        //init();

    }

}



// /////////////////////////////
// déplacements des tesselles //
// /////////////////////////////

void Plateau::deplacement(int x_old, int x_new)
{
    //
    // ajouter EXCEPTION si ( cases_libres[x][y] = false ) //
    //
    vect_tess[x_new]->SetExp(vect_tess[x_old]->GetExp());

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;
}

void Plateau::fusion(int x_old, int x_new)
{
    //
    // ajouter EXCEPTION si ( pas fusionnables ) //
    //
    vect_tess[x_new]->Fusion();

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;

    score += vect_tess[x_new]->GetScore(base);
    if(!gagne && vect_tess[x_new]->GetScore(base) == 2048) gagne = true; // on a gagné quand 2048 est atteint
    libres ++;
}

void Plateau::pointage_vect(int dir, int n)
{
    for (int k=0; k<4; k++) { // parcours des cases de chaque ligne ou colonne
        if (dir == 1) // gauche
            {vect_tess[k] = &tab[n][k]; vect_libres[k] = &cases_libres[n][k];}
        if (dir == 2) //droite
            {vect_tess[k] = &tab[n][4-k-1]; vect_libres[k] = &cases_libres[n][4-k-1];}
        if (dir == 3) // haut
            {vect_tess[k] = &tab[k][n]; vect_libres[k] = &cases_libres[k][n];}
        if (dir == 4) // bas
            {vect_tess[k] = &tab[4-k-1][n]; vect_libres[k] = &cases_libres[4-k-1][n];}
    }
}

bool Plateau::move(int dir, bool jouer)
{
    copie_tab_mem();      // on mémorise le plateau avant de le modifier
    bool a_bouge = false; // vérifie si au moins un mouvent a été fait

    for (int n=0; n<4; n++) { // parcours les lignes ou colonnes selon la direction dir
        // on fait pointer les élements de vect_tesselle vers les tesselles de chaque ligne ou colonne de tab, de gauche à droite
        // en sorte qu'un coup dans n'importe quelle direction revienne à un coup vers la gauche dans vect_tess
        // idem avec vect_libres qui pointe vers la ligne ou colonne en question de cases_libres

        pointage_vect(dir,n);

        // on réalise un coup vers la gauche dans vect_libres suivant les règles du 2048
        bool deja_fusionne [4] = {false, false, false, false}; // verifie si une case a déjà fusionné pour pas qu'elle fusionne 2 fois
        for (int j=1; j<4; j++) { // on saute la tesselle la plus à gauche (j=0) qui ne bougera pas de toute façon

            if (*vect_libres[j] == false) { // s'il y a une tesselle en indice j à considérer

                int j_avant = j; // indice de la derniere case vide à gauche
                while ((j_avant>=1) && (*vect_libres[j_avant-1] == true))
                    j_avant --;

                if (j_avant>0) { // s'il y a une autre tesselle à gauche
                    if (vect_tess[j]->GetScore(base) == vect_tess[j_avant-1]->GetScore(base)) { // s'il peut y avoir fusion
                        if (! deja_fusionne[j_avant-1]) { // si cette case n'a pas déjà fusionné
                            if (jouer) fusion(j,j_avant-1);
                            deja_fusionne[j_avant-1] = true;
                            a_bouge = true;
                        }
                        else { // si la case a déjà fusionné, elle ne doit pas fusionner 2 fois
                            if (j!=j_avant) // déplacement vers j_avant si c'est une case différente de la case actuelle
                                {if (jouer) deplacement(j,j_avant); a_bouge = true;}
                        }
                    }
                    else {// si les nombres ne sont pas identiques, il n'y a pas fusion
                        if (j!=j_avant) // déplacement vers j_avant si c'est une case différente de la case actuelle
                            {if (jouer) deplacement(j,j_avant); a_bouge = true;}
                    }
                }

                else // s'il n'y a pas de tesselle à gauche
                    {if (jouer) deplacement(j,0); a_bouge = true;} // déplacement jusqu'à l'indice 0
            }
        }
    }

    if (a_bouge && jouer) { // si le coup a conduit à un mouvement, on ajoute une nouvelle tesselle
        add_tesselle_random();
        a_deja_undo = false;
    }

    plateauMoved();

    return a_bouge;
}



// /////////////////////////////
// gestion fin de partie ///////
// /////////////////////////////
bool Plateau::a_perdu()
{
    // le joueur a perdu si aucune case n'est libre et qu'aucun mouvement n'est possible
    if (!libres) {
        bool peut_bouger = false;
        peut_bouger = move(1,false) || move(2,false) || move(3,false) || move(4,false);
        return (! peut_bouger);
    }
    return false;
}



// /////////////////////////////
// gestion option pédagogique //
// /////////////////////////////

void Plateau::copie_tab_mem()
{
    score_mem = score;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            tab_mem[i][j].SetExp(tab[i][j].GetExp());
            cases_libres_mem[i][j] = cases_libres[i][j];
        }
    }
}

void Plateau::echanger_mem()
{
    // échanger le score
    int score_aux = score;
    score = score_mem;
    score_mem = score_aux;

    // échanger tab et cases_libres
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            // échanger les valeurs de tab et de tab_mem
            int exp_aux = tab[i][j].GetExp();
            tab[i][j].SetExp(tab_mem[i][j].GetExp());
            tab_mem[i][j].SetExp(exp_aux);
            // idem pour cases_libres et cases_libres_mem
            bool case_aux = cases_libres[i][j];
            cases_libres[i][j] = cases_libres_mem[i][j];
            cases_libres_mem[i][j] = case_aux;
        }
    }
}

void Plateau::undo()
{
    if (! a_deja_undo) { // si le joueur n'est pas déjà revenu en arrière
        echanger_mem();
        a_deja_undo = true;
    }

    plateauMoved();
}

void Plateau::redo()
{
    if (a_deja_undo) { // si c'est bien après un retour en arrière
        echanger_mem();
        a_deja_undo = false;
    }
    plateauMoved();
}

void Plateau::changer_base(int b)
{
    base = b;
    init();
}

void Plateau::changer_couleurs(int c)
{
    jeuDeCouleurs = c;
    plateauMoved();
}

void Plateau::reset_best()
{
    best_score = 0;
    plateauMoved();
}
