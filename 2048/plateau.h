#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
using namespace std;

#include <QObject>
#include "tesselle.h"
#include "direction.h"

class Plateau : public QObject
{
    Q_OBJECT
public:
    explicit Plateau(QObject *parent = nullptr);

    // Q_PROPERTY(QString cptQML READ readCompteur NOTIFY cptChanged)

    Plateau();
    ~Plateau();

    bool est_plein(); // le plateau est plein ?
    bool est_vide(); // le plateau est vide ?
    void reset_table(); // vide la table de toutes les tesselles

    int get_score();
    void reset_score();
    void set_taille(int n);

    void add_tesselle(Tesselle T); // ajout d'une tesselle sur le plateau aux coordonnées (i,j)
    void add_tesselle_random(); // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre
    void init(); // création du plateau avec 1 ou 2 tesselles random

    void move_horizontal(int i,int j,int y); // déplacement horizontal de la tesselle initialement en (i,j) vers l'ordonnée y
    void move_vertical(int i,int j,int y); // déplacement vertical de la tesselle initialement en (i,j) vers l'abscisse x
    void move(Direction dir); // maj du plateau lors d'un appui sur une flèche

    bool possible_move(Direction dir); // est ce qu'un déplacement dans cette direction conduit à une modification du plateau, et donc à une progression dans le jeu ?
    bool a_perdu(); // la partie est finie ? ie. table pleine + aucun déplacement licite
    void gauche();
    void droite();
    void haut();
    void bas();

    void fusion(int i1,int j1,int i2,int j2,int x,int y); // fusionne les deux tesselles en (i1,j1) et (i2,j2) en une seule en (x,y)

    void undo(); // revenir au plateau précédent
    void redo(); // aller au plateau suivant

signals:
    void cptChanged();

public slots:


private:
    int taille;         // taille de la table nxn
    int score;
    int remplissage;    // nombre de tesselles dans le tableau
    int libres;         // nombre de cases libres

    int **tab;          // tableau d'entiers représentant les cases et les tesselles
    bool **cases_libres;// coordonnées des cases libres

    void free();        // supprime la variable dynamique tab

    int **plateau_mem;  // mémorise le plateau du coup d'avant (ou d'après)
    bool avant_ou_apres;// indique s'il s'agit du plateau suivant ou précédent
};

#endif // PLATEAU_H
