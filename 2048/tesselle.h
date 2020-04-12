#ifndef TESSELLE_H
#define TESSELLE_H
#include <iostream>
#include <QObject>
using namespace std;

class Tesselle
{
public:
    Tesselle(int exposant = 1);

    friend ostream& operator<<(ostream &sortie, Tesselle &d);

    void SetExp(int exposant);
    int GetExp();

    int GetScore(int base);
    void Fusion();

    int GetIndCouleur();  // indice de la couleur de la tesselle dans la liste des couleurs définie dans la classe Plateau
    QString GetCoulText();// couleur du nombre sur la tesselle (blanc ou gris)

private:
    int exp;
};

#endif // TESSELLE_H
