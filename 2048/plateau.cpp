#include "plateau.h"
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <QFile>
#include <QTextStream>

using namespace std;


Plateau::Plateau(QObject *parent) : QObject(parent)
{
    base = 2;
    jeuDeCouleurs = 1;
    score=0;
    for(int i=0;i<4;i++){
        best_scores[i] = 0;
    }
    srand (time(NULL));
    init(loadGame()); //initialisation du plateau à partir de la partie sauvegagardée si elle existe
}

void Plateau::init(bool dejaJoue) // initialisation des variables pour un début de partie
{
    if(dejaJoue) { //si on a deja joué au jeu et qu'une partie est sauvegardée
        // initialisation du Plateau à partir de la dernière sauvegarde
        libres = 0;
        for (int i=0; i<4; i++) { // initialisation de tab et cases_libres
            for (int j=0; j<4; j++) {
                tab[i][j].SetExp(partieStockee[j+4*i]);
                if (partieStockee[j+4*i] == 0) {
                    cases_libres[i][j] = true;
                    libres++;
                }
            }
        }
        score = partieStockee[16];

        if (partieStockee[17])
            {gagne = true; gagne_mais_continue = true;}
        else
            {gagne = false; gagne_mais_continue = false;}
        base = partieStockee[18];
        for(int i=0; i<4; i++)
            best_scores[i] = partieStockee[19+i];
    }

    else { // si c'est la première fois qu'on joue OU en cours d'execution lors d'une nouvelle partie
        // initialisation du Plateau vide
        score = 0;
        for (int i=0; i<4; i++) { // initialisation de tab et cases_libres
            for (int j=0; j<4; j++) {
                tab[i][j].SetExp(0);
                cases_libres[i][j] = true;
            }
        }
        libres = 16;
        add_tesselle_random(); add_tesselle_random(); // 2 tesselles pour commencer
        gagne = false; gagne_mais_continue = false;
    }

    score_undo.clear(); score_redo.clear();
    score_undo.push_back(score);

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
            tab[i][j].coup(); // mise en mémoire du plateau initial
    }

    // signaux pour QML
    partieDebOuFin();
    plateauMoved();

}



// /////////////////////////////
// interaction QML /////////////
// /////////////////////////////

QList<QString> Plateau::readMove()
{
    QList<QString> listNombres;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
            listNombres.append(QString::number(tab[i][j].GetScore(base)));
    }
    return listNombres;
}

QList<bool> Plateau::readVisible()
{
    QList<bool> visibles;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
            visibles.append((tab[i][j].GetExp() > 0));
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
    scores.append(QString::number(score)); // score courant
    scores.append(QString::number(best_scores[getIndBest()])); // meilleur score
    return scores;
}

QList<bool> Plateau::readFinPartie() // visible true/false pour calque gagné/perdu (dans cet ordre)
{
    QList<bool> ls_visibleGP;

    if (a_perdu()) {
        ls_visibleGP.append(false);
        ls_visibleGP.append(true);
    }else if(gagne && !gagne_mais_continue){
        ls_visibleGP.append(true);
        ls_visibleGP.append(false);
    }else{
        ls_visibleGP.append(false);
        ls_visibleGP.append(false);
    }

    return ls_visibleGP;
}

ostream& operator<<(ostream &sortie, Plateau &p) {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
                sortie << p.tab[i][j] << " ";
        sortie << endl;
    };
    return sortie;
}



// /////////////////////////////
// ajout des tesselles /////////
// /////////////////////////////

void Plateau::add_tesselle(int exp, int i, int j) // ajouter la tesselle d'exposant exp au plateau en (i,j)
{
    tab[i][j].SetExp(exp);
    cases_libres[i][j] = false;
    libres --;
}

void Plateau::add_tesselle_random() // ajoute une tesselle (2 ou 4) de façon aléatoire sur une case libre
{
    int b = rand() % libres; // case libre au hazard
    int c = 0;               // compteur
    int iplat=0; int jplat=0;    // coordonnées de la nouvelle tesselle

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            if (cases_libres[i][j]) { // on cherche la b-ième case libre
                if (c == b)
                    {iplat = i; jplat = j;}
                c++; // ou le meilleur électif
            }
        }
    }
    int exp = 1;
    int proba = rand() % 5; // 1 chance sur 5 d'avoir un 4, sinon un 2
    if (proba == 0) {exp = 2;}

    add_tesselle(exp,iplat,jplat);

    if (a_perdu()) {
        partieDebOuFin();
    }
}



// /////////////////////////////
// déplacements des tesselles //
// /////////////////////////////

void Plateau::deplacement(int x_old, int x_new) // déplacer la tesselle initialement en x_old vers x_new dans le vecteur vect_tess
{
    vect_tess[x_new]->SetExp(vect_tess[x_old]->GetExp());
    vect_tess[x_old]->SetExp(0);

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;
}

void Plateau::fusion(int x_old, int x_new) // fusionne les deux tesselles en x_old et x_new en une seule en x_new
{
    vect_tess[x_old]->SetExp(0);
    vect_tess[x_new]->Fusion();

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;

    libres ++;
    score += vect_tess[x_new]->GetScore(base);
    if(score > best_scores[getIndBest()])
        best_scores[getIndBest()] = score;

    if(!gagne && vect_tess[x_new]->GetExp() == 11) {
        gagne = true; // on a gagné quand 2048 (ou équivalent) est atteint
        partieDebOuFin();
    }
}

void Plateau::pointage_vect(int dir, int n) // fait pointer les attributs vect_tess et vect_libres vers n-ième ligne ou colonne, dans la direction dir de tab et cases_libres
{
    for (int k=0; k<4; k++) { // parcours des cases de chaque ligne ou colonne
        if (dir == 1) // gauche -> n-ième ligne de gauche à droite
            {vect_tess[k] = &tab[n][k]; vect_libres[k] = &cases_libres[n][k];}
        if (dir == 2) //droite -> n-ième ligne de droite à gauche
            {vect_tess[k] = &tab[n][4-k-1]; vect_libres[k] = &cases_libres[n][4-k-1];}
        if (dir == 3) // haut -> n-ième colonne de haut en bas
            {vect_tess[k] = &tab[k][n]; vect_libres[k] = &cases_libres[k][n];}
        if (dir == 4) // bas -> n-ième colonne de bas en haut
            {vect_tess[k] = &tab[4-k-1][n]; vect_libres[k] = &cases_libres[4-k-1][n];}
    }
}

bool Plateau::move(int dir, bool jouer) // maj du plateau lors d'un appui sur une flèche
// si jouer = false, on vaut juste vérifier si le coup mène à un déplacement, sans le jouer
{
    bool a_bouge = false; // vérifie si au moins un mouvent a été fait

    for (int n=0; n<4; n++) { // parcours les lignes ou colonnes selon la direction dir
        // on fait pointer les élements de vect_tesselle vers les tesselles de chaque ligne ou colonne de tab, de gauche à droite
        // en sorte qu'un coup dans n'importe quelle direction revienne à un coup vers la gauche dans vect_tess
        // idem avec vect_libres qui pointe vers la ligne ou colonne en question de cases_libres

        pointage_vect(dir,n);

        // on réalise un coup vers la gauche dans vect_libres suivant les règles du 2048
        bool deja_fusionne [4] = {false, false, false, false}; // verifie si une case a déjà fusionné pour pas qu'elle fusionne 2 fois
        for (int j=1; j<4; j++) { // on parcourt les cases de vect_tesselle
            // on saute la tesselle la plus à gauche (j=0) qui ne bougera pas de toute façon

            if (*vect_libres[j] == false) { // s'il y a une tesselle sur la case en indice j

                int j_avant = j; // on calcule j_avant, l'indice de la derniere case vide à gauche
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
        add_tesselle_random(); // le jeu continue : ajout d'une nouvelle tesselle, et il y a forcément la place
                               // car il y a eu un mouvement à ce coup, donc au moins une case vide
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++)
                tab[i][j].coup(); // mise en mémoire du coup joué dans la classe Tesselle
        }
        score_undo.push_back(score); // mise en mémoire du score obtenu
        score_redo.clear();
        plateauMoved();
    }

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

void Plateau::continuer()
{
    gagne_mais_continue = true;
    partieDebOuFin();
}



// /////////////////////////////
// gestion option pédagogique //
// /////////////////////////////

void Plateau::undo()
{
    if (score_undo.size() > 1) {
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                tab[i][j].undo();
                if (tab[i][j].GetExp() == 0) cases_libres[i][j] = true;
                else cases_libres[i][j] = false;
            }
        }
        score_redo.push_back(score);
        score_undo.pop_back();
        score = score_undo.back();
        plateauMoved();
    }
}

void Plateau::redo()
{
    if (score_redo.size() >= 1) {
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                tab[i][j].redo();
                if (tab[i][j].GetExp() == 0) cases_libres[i][j] = true;
                else cases_libres[i][j] = false;
            }
        }
        score_undo.push_back(score_redo.back());
        score_redo.pop_back();
        score = score_undo.back();
        plateauMoved();
    }
}



// /////////////////////////////
// gestion du menu /////////////
// /////////////////////////////

void Plateau::changer_base(int b) // change la base, par défaut 2, peut être changé en 3, 5 ou 7
{
    base = b;
    init(false);
}

int Plateau::getIndBest() // donne l'indice correspondant à la base utilisée, pour avoir le best score
                          // correspondant à la base choisie
{
    int r=0;
    switch(base) {
        case 2:
            r= 0;
            break;
        case 3:
            r= 1;
            break;
        case 5:
            r= 2;
            break;
        case 7:
            r=3;
            break;
    }
    return r;
}

void Plateau::changer_couleurs(int c) // change le set de couleurs utilisé pour les tesselles
{
    jeuDeCouleurs = c;
    plateauMoved();
}

void Plateau::reset_best()
{
    best_scores[getIndBest()] = 0;
    plateauMoved();
}



// /////////////////////////////////////////////////
// gestion de la sauvegarde de la dernière partie //
// /////////////////////////////////////////////////

void Plateau::saveGame(){   // sauvegarde la partie en cours lors de la fermeture de l'application
    QList<int> QTableau;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            QTableau.append(tab[i][j].GetExp()); // sauvegarde des exposants de chaque tesselle dans l'ordre
        }
    }
    QTableau.append(score);        // sauvegarde du score courant
    if(gagne){       // sauvegarde l'état "a gagné ou non"
        QTableau.append(1);
    }else{
        QTableau.append(0);
    }
    QTableau.append(base);
    for(int i=0;i<4;i++){       // sauvegarde des meilleurs scores pour chaque base
        QTableau.append(best_scores[i]);
    }
    QString filename="DernierePartie.dat";  // fichier .dat créé ou modifié dans le repertoire local
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QDataStream out( &file );
        out << QTableau;    // le fichier contient désormais la QList<int> QTableau et uniquement celle-ci
    }
}

bool Plateau::loadGame(){
    QFile file("DernierePartie.dat");
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        QList<int> QTableau;
        in >> QTableau; // charge la QList contenue dans le fichier .dat
        for(int i=0;i<23;i++){
            partieStockee[i] = QTableau[i];
        }
        return true; // renvoie true si le fichier existe
    }
    return false; // false sinon
}

