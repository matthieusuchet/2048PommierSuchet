#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <QObject>
#include <QMenuBar>
using namespace std;

#include "tesselle.h"

class Plateau : public QObject
{
    Q_OBJECT
public:

    explicit Plateau(QObject *parent = nullptr); // constructeur
    Q_INVOKABLE void init(); // vide la table et ajoute 2 tesselles pour commencer la partie


    /// interaction avec QML
    //propriétés d'objets QML modifiables depuis le C++
    Q_PROPERTY(QList<QString> nombreQML READ readMove NOTIFY plateauMoved)
    Q_PROPERTY(QList<bool> visibleQML READ readVisible NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> couleurQML READ readCouleur NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> couleurtextQML READ readCoulText NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> scoresQML READ readScores NOTIFY plateauMoved)
    Q_PROPERTY(QList<bool> finPartieQML READ readFinPartie NOTIFY partieDebOuFin)

    //lecture de ces propriétés depuis le C++ vers le QML
    QList<QString> readMove();
    QList<bool> readVisible();
    QList<QString> readCouleur();
    QList<QString> readCoulText();
    QList<QString> readScores();
    QList<bool> readFinPartie();


    friend ostream& operator<<(ostream &sortie, Plateau &d); // opérateur <<

    /// gestion du jeu
    // ajout des tesselles
    void add_tesselle(Tesselle T); // ajout d'une tesselle sur le plateau aux coordonnées (i,j)
    void add_tesselle_random(); // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre

    // déplacement des tesselles
    void deplacement(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new); // déplacer la tesselle initialement en x_old vers x_new dans le vecteur vect_tess
    void fusion(Tesselle* vect_tess, bool* vect_libres, int x_old, int x_new); // fusionne les deux tesselles en x_old et x_new en une seule en x_new

    bool gauche_ligne(Tesselle* vect_tess, bool* vect_libres); // réalise un coup vers la gauche dans vect_libres (vecteur de 4 tesselles) suivant les règles du 2048
    Q_INVOKABLE void move(int dir); // maj du plateau lors d'un appui sur une flèche

    // gestion fin de partie
    bool possible_move(int dir); // est ce qu'un déplacement dans cette direction conduit à une modification du plateau, et donc à une progression dans le jeu ?
    bool a_perdu(); // la partie est finie ? ie. table pleine + aucun déplacement licite

    // gestion option pédagogique
    Q_INVOKABLE void undo(); // revenir au plateau précédent
    void redo(); // aller au plateau suivant
    void copie_tab_mem(); // copier tab dans tab_mem [option pédagogique]
    void echanger_mem(); // échanger les valeurs de tab et de tab_mem

    Q_INVOKABLE void changer_base(int b);

signals:
    void plateauMoved();   // appelé à chaque déplacement des tesselles pour MAJ l'affichage
    void partieDebOuFin(); // appelé au début et à la fin de chaque partie pour cacher/afficher les calques "perdu"/"gagné"

private:
    int score;
    int best_score;
    int libres;              // nombre de cases libres
    int base;

    Tesselle tab [4][4];     // tableau de Tesselles représentant les cases et les tesselles
    bool cases_libres [4][4];// coordonnées des cases libres

    Tesselle tab_mem [4][4];     // mémorise le plateau du coup d'avant (ou d'après)
    bool cases_libres_mem [4][4];// coordonnées des cases libres
    int score_mem;    // mémorise le score du coup d'avant
    bool a_deja_undo; // indique s'il s'agit du plateau suivant ou précédent
    bool gagne;  // vrai si 2048 a été atteint

    // liste des couleurs classiques pour les tesselles
    QString liste_coul [12] = {"#ece4db","#ebe0cb","#e9b381","#e8996c","#e78267","#e56847","#e9cf7f","#e8cc72","#edcb60","#ecc84f","#edc43d","#eec22e","#77a135"};

};

#endif // PLATEAU_H
