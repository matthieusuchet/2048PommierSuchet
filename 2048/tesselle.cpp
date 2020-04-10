#include "tesselle.h"
#include <math.h>

Tesselle::Tesselle(int nombre, int iplat, int jplat)
{
    nb = nombre;
    i = iplat;
    j = jplat;
}

Tesselle::Tesselle()
{
    Tesselle(2,0,0);
}

ostream& operator<<(ostream &sortie, Tesselle &d) { // opérateur <<
    sortie << d.nb;
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
int Tesselle::GetScore()
{
    return nb;
}

void Tesselle::Fusion()
{
    nb = 2 * nb;
}

// Couleur //
int Tesselle::GetIndCouleur()
{
    return std::log2(nb) - 1;
}

QString Tesselle::GetCoulText()
{
    if (nb <= 4)
        return "#766e66";
    else
        return "#f9f6f2";
}
