#include "tesselle.h"
#include <math.h>

Tesselle::Tesselle(int exposant)
{
    exp = exposant;
}


ostream& operator<<(ostream &sortie, Tesselle &t) {
    sortie << t.exp;
    return sortie;
}

// Score //
void Tesselle::SetExp(int exposant)
{
    exp = exposant;
}

int Tesselle::GetExp()
{
    return exp;
}

int Tesselle::GetScore(int base)
{
    int nb = pow(base,exp);
    return nb;
}

void Tesselle::Fusion()
{
    exp++;
}

void Tesselle::coup()
{
    memoire_undo.push_back(exp);
    memoire_redo.clear();
}


void Tesselle::undo()
{
    if (memoire_undo.size() >= 1) {
        memoire_redo.push_back(exp);
        memoire_undo.pop_back();
        exp = memoire_undo.back();

    }
}

void Tesselle::redo()
{
    if (memoire_redo.size() >= 1) {
        memoire_undo.push_back(memoire_redo.back());
        memoire_redo.pop_back();
        exp = memoire_undo.back();
    }
}

// Couleur //
int Tesselle::GetIndCouleur()
{
    int ind = exp;
    return ind;
}

QString Tesselle::GetCoulText()
{
    if (exp <= 2)
        return "#766e66";
    else
        return "#f9f6f2";
}
