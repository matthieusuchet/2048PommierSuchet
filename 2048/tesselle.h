#ifndef TESSELLE_H
#define TESSELLE_H
#include <iostream>
#include <QObject>
using namespace std;

class Tesselle
{
public:
    Tesselle(int nombre, int iplat, int jplat);
    Tesselle();

    friend ostream& operator<<(ostream &sortie, Tesselle &d);

    void SetPosition(int i, int j);
    int GetI();
    int GetJ();

    int GetScore();
    void Fusion();

    int GetIndCouleur();  // indice de la couleur de la tesselle dans la liste des couleurs définie dans la classe Plateau
    QString GetCoulText();// couleur du nombre sur la tesselle (blanc ou gris)

private:
    int nb;
    int i;
    int j;
};

#endif // TESSELLE_H
