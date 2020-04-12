#include "tesselle.h"
#include <math.h>

Tesselle::Tesselle(int exposant)
{
    exp = exposant;
    cout << '1';
}


ostream& operator<<(ostream &sortie, Tesselle &d) {
    sortie << d.exp;
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

// Couleur //
int Tesselle::GetIndCouleur()
{
    int ind = exp-1;
    return ind;
}

QString Tesselle::GetCoulText()
{
    if (exp <= 2)
        return "#766e66";
    else
        return "#f9f6f2";
}
