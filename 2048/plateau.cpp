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
    best_score = 0;
    srand (time(NULL));
    init(loadGame()); //initialisation du plateau à partir de la partie sauvegagardée si elle existe
}

void Plateau::init(bool dejaJoue) // initialisation des variables pour un début de partie
{
    if(dejaJoue){   //si on a deja joué au jeu et qu'une partie est sauvegardée
        libres = 0;
        for (int i=0; i<4; i++) { // initialisation de tab et cases_libres
            for (int j=0; j<4; j++) {
                tab[i][j].SetExp(partieStockee[j+4*i]);
                if(partieStockee[j+4*i] == 0){
                    cases_libres[i][j] = true;
                    libres++;
                }
            }
        }
        score = partieStockee[16];
        best_score = partieStockee[17];
        if(partieStockee[18]){
            gagne = true; gagne_mais_continue = true;
        }else{
            gagne = false; gagne_mais_continue = false;
        }
    }else{        // si c'est la première fois qu'on joue OU en cours d'execution lors d'une nouvelle partie
        if (score > best_score) // mise à jour du meilleur score
            best_score = score;
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

QList<QString> Plateau::readMove(){
    QList<QString> listNombres;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++)
            listNombres.append(QString::number(tab[i][j].GetScore(base)));
    }
    return listNombres;
}

QList<bool> Plateau::readVisible(){
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
    scores.append(QString::number(score));      // score courant
    scores.append(QString::number(best_score)); // meilleur score
    return scores;
}



QList<bool> Plateau::readFinPartie(){
    QList<bool> ls_visibleGP;  // visible true/false
                               //pour calque gagné/perdu (dans cet ordre)

    if(a_perdu()){
        ls_visibleGP.append(false);
        ls_visibleGP.append(true);
    }else if(gagne && !gagne_mais_continue){
        ls_visibleGP.append(true);
        ls_visibleGP.append(false);
    }else{
        ls_visibleGP.append(false);
        ls_visibleGP.append(false);
    }

    /*
    if(score){
        if(gagne && !gagne_mais_continue){
            ls_visibleGP.append(true);
            ls_visibleGP.append(false);
        }else if(a_perdu()){
            ls_visibleGP.append(false);
            ls_visibleGP.append(true);
        }else if(gagne_mais_continue && !a_perdu()){
            ls_visibleGP.append(false);
            ls_visibleGP.append(false);
        }
    }else{      // score=0 -> début de partie
        ls_visibleGP.append(false);
        ls_visibleGP.append(false);
    }
    */

    return ls_visibleGP;
}

///

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
    vect_tess[x_new]->SetExp(vect_tess[x_old]->GetExp());
    vect_tess[x_old]->SetExp(0);

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;
}

void Plateau::fusion(int x_old, int x_new)
{
    vect_tess[x_old]->SetExp(0);
    vect_tess[x_new]->Fusion();

    *vect_libres[x_old] = true;
    *vect_libres[x_new] = false;

    score += vect_tess[x_new]->GetScore(base);
    if(score>best_score) best_score=score;

    if(!gagne && vect_tess[x_new]->GetExp() == 4){
        gagne = true; // on a gagné quand 2048 (ou équivalent) est atteint
        partieDebOuFin();
    }
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
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++)
                tab[i][j].coup(); // mise en mémoire du coup joué dans la classe Tesselle
        }
        score_undo.push_back(score);
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

void Plateau::continuer(){
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
    if (score_redo.size() > 1) {
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

void Plateau::changer_base(int b)
{
    base = b;
    init(false);
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

/// /////////////////////////////////////////////////
/// gestion de la sauvegarde de la dernière partie //
/// /////////////////////////////////////////////////


void Plateau::saveGame(){   // sauvegarde la partie en cours lors de la fermeture de l'application
    QList<int> QTableau;
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            QTableau.append(tab[i][j].GetExp()); // sauvegarde des exposants de chaque tesselle dans l'ordre
        }
    }
    QTableau.append(score);        // sauvegarde du score et du meilleur score
    QTableau.append(best_score);
    if(gagne){       // sauvegarde l'état "a gagné ou non"
        QTableau.append(1);
    }else{
        QTableau.append(0);
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
        in >> QTableau;     // charge la QList contenue dans le fichier .dat
        for(int i=0;i<19;i++){
            partieStockee[i] = QTableau[i];
        }
        return true;    // renvoie true si le fichier existe
    }
    return false;       // false sinon
}

