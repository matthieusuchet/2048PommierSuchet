#ifndef TESSELLE_H
#define TESSELLE_H
#include <iostream>
#include <QObject>
using namespace std;

class Tesselle
{
public:
    Tesselle(int nombre, int couleur, int iplat, int jplat);
    Tesselle();

    friend bool operator==(const Tesselle &t1, const Tesselle &t2);
    friend ostream& operator<<(ostream &sortie, Tesselle &d); // opérateur <<

    void SetPosition(int i, int j);
    QString GetCouleur();
    QString GetCoulText();
    void IncrCoul();
    int GetScore();
    int GetI();
    int GetJ();
    void Fusion();

private:
    int nb;
    int indice_coul;
    QString liste_coul [12] = {"#ece4db","#ebe0cb","#e9b381","#e8996c","#e78267","#e56847","#e9cf7f","#e8cc72","#e8c865","#e8c865","#e8c865","#e8c865"};
    // QString couleurs[11]={"#edebe7", "#d4cdb4", "#d4a56b", "#ed8251", "#dd6151", "#e62c19", "#d4bf6d", "#ebcb58", "#d6b53a", "#d2a913", "#f7cb2e"};
    QString coul_texte;
    int i;
    int j;
};

#endif // TESSELLE_H
