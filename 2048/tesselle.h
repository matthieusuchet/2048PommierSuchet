#ifndef TESSELLE_H
#define TESSELLE_H
#include <iostream>
#include <QObject>
#include <vector>
using namespace std;

class Tesselle
{
public:
    Tesselle(int exposant = 0);

    friend ostream& operator<<(ostream &sortie, Tesselle &t);

    void SetExp(int exposant);
    int GetExp();

    int GetScore(int base);
    void Fusion();

    void coup();
    void undo();
    void redo();

    int GetIndCouleur();  // indice de la couleur de la tesselle dans la liste des couleurs définie dans la classe Plateau
    QString GetCoulText();// couleur du nombre sur la tesselle (blanc ou gris)

private:
    int exp;
    vector <int> memoire_undo; // mise en mémoire des coups passés
    vector <int> memoire_redo;  // mise en mémoire des coups d'après, se remplit suite à un undo()
};

#endif // TESSELLE_H
