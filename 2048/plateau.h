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
    Q_INVOKABLE void init(bool dejaJoue); // initialisation du plateau en début de partie


    /// interaction avec QML

    // propriétés d'objets QML modifiables depuis le C++
    Q_PROPERTY(QList<QString> nombreQML READ readMove NOTIFY plateauMoved) // nombres écrit sur les cases
    Q_PROPERTY(QList<bool> visibleQML READ readVisible NOTIFY plateauMoved) // cases visibles ou non
    Q_PROPERTY(QList<QString> couleurQML READ readCouleur NOTIFY plateauMoved) // couleur des cases
    Q_PROPERTY(QList<QString> couleurtextQML READ readCoulText NOTIFY plateauMoved) // couleur du nombre sur la case
    Q_PROPERTY(QList<QString> scoresQML READ readScores NOTIFY plateauMoved) // score de la partie en cours
    Q_PROPERTY(QList<bool> finPartieQML READ readFinPartie NOTIFY partieDebOuFin) // affichage de calques gagné/perdu

    // lecture de ces propriétés depuis le C++ vers le QML
    QList<QString> readMove();
    QList<bool> readVisible();
    QList<QString> readCouleur();
    QList<QString> readCoulText();
    QList<QString> readScores();
    QList<bool> readFinPartie();

    friend ostream& operator<<(ostream &sortie, Plateau &d);


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
    Q_INVOKABLE void continuer(); // continuer à jouer après avoir atteint 2048

    // gestion option pédagogique
    Q_INVOKABLE void undo(); // revenir au plateau précédent
    Q_INVOKABLE void redo(); // aller au plateau suivant

    // gestion du menu
    Q_INVOKABLE void changer_base(int b);    // change la base, par défaut 2, peut être changé en 3, 5 ou 7
    Q_INVOKABLE void changer_couleurs(int c);// change le set de couleurs utilisé pour les tesselles
    Q_INVOKABLE void reset_best(); // réinitialise le meilleur score
    int getIndBest(); // donne l'indice correspondant à la base utilisée pour avoir le best score correspondant à la base choisie

    // gestion de la sauvegarde de la dernière partie
    Q_INVOKABLE void saveGame();
    bool loadGame();


signals:

    void plateauMoved();   // appelé à chaque déplacement des tesselles pour MAJ l'affichage
    void partieDebOuFin(); // appelé au début et à la fin de chaque partie pour cacher/afficher les calques "perdu"/"gagné"


private:

    int score;
    int best_scores[4]; // best pour chaque base
    int libres; // nombre de cases libres
    int base;
    int partieStockee[23]; // initialiser ?

    // tableaux pour représenter la partie en cours
    Tesselle tab [4][4];      // tableau de Tesselles représentant les cases et les tesselles
    bool cases_libres [4][4]; // coordonnées des cases libres

    // tableaux de pointeurs utilisés pour les déplacements, ils sont cronstruits par pointage_vect(int dir, int n)
    Tesselle* vect_tess[4]; // pointeurs sur les tesselles de tab
    bool *vect_libres[4];   // pointeurs sur les booléens de cases_libres

    vector<int> score_undo; // mémorise les score des coups d'avant
    vector<int> score_redo; // mémorise les score des coups d'après

    bool gagne;  // vrai si 2048 a été atteint
    bool gagne_mais_continue; // vrai si gagne=true et on continue à jouer

    // liste des couleurs classiques pour les tesselles
    QString liste_coul [18] = {"#ece4db","#ece4db","#ebe0cb","#e9b381","#e8996c","#e78267","#e56847","#e9cf7f","#e8cc72","#edcb60","#ecc84f","#edc43d","#eec22e","#77a135","#77a135","#77a135","#77a135","#77a135"};
    // couleurs bleu
    QString liste_coul_bleu [18] = {"#dae9f9","#dae9f9","#c8cae7","#7ebce8","#7ecce7","#81c7b7","#71c2ac","#6365ac","#5357a2","#4c519f","#414d9c","#3b4b9b","#974292","#974292","#974292","#974292","#974292","#974292"};
    // couleurs jaune/vert
    QString liste_coul_vert [18] = {"#f9f7d1","#f9f7d1","#e0eabc","#f7ec67","#feee55","#ffdb4d","#ffd52a","#97c349","#8dbe29","#7fba28","#78b82a","#71b62b","#2db6b9","#2db6b9","#2db6b9","#2db6b9","#2db6b9","#2db6b9"};
    int jeuDeCouleurs;
};

#endif // PLATEAU_H
