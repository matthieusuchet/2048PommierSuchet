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

ostream& operator<<(ostream &sortie, Tesselle &d) {
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

void Tesselle::Fusion(int base)
{
    nb = base * nb;
}

// Couleur //
int Tesselle::GetIndCouleur(int base)
{
    return (int)((std::log(nb) / std::log(base)) -1);
}

QString Tesselle::GetCoulText(int base)
{
    if (nb <= base*base)
        return "#766e66";
    else
        return "#f9f6f2";
}
