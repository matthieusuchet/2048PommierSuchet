#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <vector>
using namespace std;

#include "tesselle.h"

class Plateau
{
public:

    Plateau(); // constructeur

    friend ostream& operator<<(ostream &sortie, Plateau &d); // opérateur <<

    bool est_plein(); // le plateau est plein ?
    void init(); // vide la table et ajoute 2 tesselles pour commencer la partie
    int get_score();

    // ajout des tesselles
    void add_tesselle(Tesselle T); // ajout d'une tesselle sur le plateau aux coordonnées (i,j)
    void add_tesselle_random(); // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre

    // déplacement des tesselles
    void deplacement(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new); // déplacer la tesselle initialement en x_old vers x_new dans le vecteur vect_tess
    void fusion(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new); // fusionne les deux tesselles en x_old et x_new en une seule en x_new
    bool gauche_ligne(Tesselle* vect_tess, bool* vect_libres); // réalise un coup vers la gauche dans vect_libres (vecteur de 4 tesselles) suivant les règles du 2048
    bool move(int dir); // maj du plateau lors d'un appui sur une flèche

    // gestion fin de partie
    bool possible_move(int dir); // est ce qu'un déplacement dans cette direction conduit à une modification du plateau, et donc à une progression dans le jeu ?
    bool a_perdu(); // la partie est finie ? ie. table pleine + aucun déplacement licite

    // gestion option pédagogique
    void undo(); // revenir au plateau précédent
    void redo(); // aller au plateau suivant
    void copie_tab_mem(); // copier tab dans tab_mem [option pédagogique]
    void echanger_mem(); // échanger les valeurs de tab et de tab_mem
    void mise_a_jour_score(); // mettre à jour le score en cas de changement de plateau

private:
    int score;
    int best_score;
    int remplissage;         // nombre de tesselles dans le tableau
    int libres;              // nombre de cases libres

    Tesselle tab [4][4];     // tableau d'entiers représentant les cases et les tesselles
    bool cases_libres [4][4];// coordonnées des cases libres

    Tesselle tab_mem [4][4];     // mémorise le plateau du coup d'avant (ou d'après)
    bool cases_libres_mem [4][4];// coordonnées des cases libres
    bool a_deja_undo;        // indique s'il s'agit du plateau suivant ou précédent
};

#endif // PLATEAU_H
