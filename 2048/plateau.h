#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <QObject>
#include <QMenuBar>
#include <vector>
using namespace std;

#include "tesselle.h"

class Plateau : public QObject
{
    Q_OBJECT
public:

    explicit Plateau(QObject *parent = nullptr); // constructeur
    Q_INVOKABLE void init(); // vide la table et ajoute 2 tesselles pour commencer la partie


    /// interaction avec QML
    // propriétés d'objets QML modifiables depuis le C++
    Q_PROPERTY(QList<QString> nombreQML READ readMove NOTIFY plateauMoved)
    Q_PROPERTY(QList<bool> visibleQML READ readVisible NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> couleurQML READ readCouleur NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> couleurtextQML READ readCoulText NOTIFY plateauMoved)
    Q_PROPERTY(QList<QString> scoresQML READ readScores NOTIFY plateauMoved)
    Q_PROPERTY(QList<bool> finPartieQML READ readFinPartie NOTIFY partieDebOuFin)

    // lecture de ces propriétés depuis le C++ vers le QML
    QList<QString> readMove();
    QList<bool> readVisible();
    QList<QString> readCouleur();
    QList<QString> readCoulText();
    QList<QString> readScores();
    QList<bool> readFinPartie();

    friend ostream& operator<<(ostream &sortie, Plateau &d); // opérateur <<


    /// gestion du jeu
    // ajout des tesselles
    void add_tesselle(int exp, int i, int j); // ajout d'une tesselle sur le plateau aux coordonnées (i,j)
    void add_tesselle_random(); // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre

    // déplacement des tesselles
    void deplacement(int x_old, int x_new); // déplacer la tesselle initialement en x_old vers x_new dans le vecteur vect_tess
    void fusion(int x_old, int x_new); // fusionne les deux tesselles en x_old et x_new en une seule en x_new
    void pointage_vect(int dir, int n); // fait pointer les attributs vect_tess et vect_libres vers n-ième ligne ou colonne, dans la direction dir de tab et cases_libres
    Q_INVOKABLE bool move(int dir, bool jouer = true); // maj du plateau lors d'un appui sur une flèche
                                                       // si jouer = false, on vaut juste vérifier si le coup mène à un déplacement, sans le jouer

    // gestion fin de partie
    bool a_perdu(); // la partie est finie ? ie. table pleine + aucun déplacement licite
    Q_INVOKABLE void continuer();    // continuer à jouer après avoir atteint 2048

    // gestion option pédagogique
    Q_INVOKABLE void undo(); // revenir au plateau précédent
    Q_INVOKABLE void redo(); // aller au plateau suivant
    void copie_tab_mem(); // copier tab dans tab_mem [option pédagogique]
    void echanger_mem(); // échanger les valeurs de tab et de tab_mem

    Q_INVOKABLE void changer_base(int b);
    Q_INVOKABLE void changer_couleurs(int c);

    Q_INVOKABLE void reset_best();

signals:
    void plateauMoved();   // appelé à chaque déplacement des tesselles pour MAJ l'affichage
    void partieDebOuFin(); // appelé au début et à la fin de chaque partie pour cacher/afficher les calques "perdu"/"gagné"

private:
    int score;
    int best_score;
    int libres; // nombre de cases libres
    int base;

    // tableaux pour représenter la partie en cours
    Tesselle tab [4][4];      // tableau de Tesselles représentant les cases et les tesselles
    bool cases_libres [4][4]; // coordonnées des cases libres

    // tableaux de pointeurs utilisés pour les déplacements, ils sont cronstruits par pointage_vect(int dir, int n)
    Tesselle* vect_tess[4]; // pointeurs sur les tesselles de tab
    bool *vect_libres[4];   // pointeurs sur les booléens de cases_libres

    Tesselle tab_mem [4][4];     // mémorise le plateau du coup d'avant (ou d'après)
    bool cases_libres_mem [4][4];// coordonnées des cases libres
    int score_mem;    // mémorise le score du coup d'avant
    bool a_deja_undo; // indique s'il s'agit du plateau suivant ou précédent
    bool gagne;  // vrai si 2048 a été atteint
    bool gagne_mais_continue; // vrai si gagne=true et on continue à jouer

    // liste des couleurs classiques pour les tesselles
    QString liste_coul [17] = {"#ece4db","#ebe0cb","#e9b381","#e8996c","#e78267","#e56847","#e9cf7f","#e8cc72","#edcb60","#ecc84f","#edc43d","#eec22e","#77a135","#77a135","#77a135","#77a135","#77a135"};
    // couleurs bleu
    QString liste_coul_bleu [17] = {"#dae9f9","#c8cae7","#7ebce8","#7ecce7","#81c7b7","#71c2ac","#6365ac","#5357a2","#4c519f","#414d9c","#3b4b9b","#974292","#974292","#974292","#974292","#974292","#974292"};
    // couleurs jaune/vert
    QString liste_coul_vert [17] = {"#f9f7d1","#e0eabc","#f7ec67","#feee55","#ffdb4d","#ffd52a","#97c349","#8dbe29","#7fba28","#78b82a","#71b62b","#2db6b9","#2db6b9","#2db6b9","#2db6b9","#2db6b9","#2db6b9"};
    int jeuDeCouleurs;
};

#endif // PLATEAU_H
