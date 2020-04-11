#include "tesselle.h"
#include <math.h>

Tesselle::Tesselle(int exposant, int iplat, int jplat)
{
    exp = exposant;
    i = iplat;
    j = jplat;
}

Tesselle::Tesselle()
{
    Tesselle(1,0,0);
}

ostream& operator<<(ostream &sortie, Tesselle &d) {
    sortie << d.exp;
    return sortie;
}

// Position //
void Tesselle::SetPosition(int I, int J)
{
    i = I; j = J;
}

int Tesselle::GetI()
{
    return i;
}

int Tesselle::GetJ()
{
    return j;
}

// Score //
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
