#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
using namespace std;


class Plateau
{
public:
    Plateau();
    ~Plateau();

    void set_taille(int n);
    void init(); // création du plateau avec 1 ou 2 tesselles random

    void add_tesselle(Tesselle T,int i,int j); // ajout d'une tesselle sur le plateau aux coordonnées (i,j)
    void add_tesselle_random(); // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre


    // Déplacement des tesselles
    void move_horizontal(int i,int j,int y); // déplacement horizontal de la tesselle initialement en (i,j) vers l'ordonnée y
    void move_vertical(int i,int j,int y); // déplacement vertical de la tesselle initialement en (i,j) vers l'abscisse x
    void move(Direction dir); // maj du plateau lors d'un appui sur une flèche

    bool possible_move(Direction dir); // est ce qu'un déplacement dans cette direction conduit à une modification du plateau, et donc à une progression dans le jeu ?
    void gauche();
    void droite();
    void haut();
    void bas();

    void fusion(int i1,int j1,int i2,int j2,int x,int y); // fusionne les deux tesselles en (i1,j1) et (i2,j2) en une seule en (x,y)


    // Partie
    int get_score();
    void reset_score();

    bool est_plein(); // le plateau est plein ?
    bool est_vide(); // le plateau est vide ?
    bool a_perdu(); // la partie est finie ? ie. table pleine + aucun déplacement licite
    void reset_table(); // vide la table de toutes les tesselles

    void undo(); // revenir au plateau précédent
    void redo(); // aller au plateau suivant

private:
    int taille; // taille de la table nxn
    int **tab; // tableau d'entiers représentant les cases et les tesselles
    int score;

    int remplissage; // nombre de tesselles dans le tableau
    bool **cases_libres; // coordonnées des cases libres

    int **plateau_mem; // mémorise le plateau du coup d'avant (ou d'après)
    bool avant_ou_apres; //  indique s'il s'agit du plateau suivant ou précédent
};

#endif // PLATEAU_H
