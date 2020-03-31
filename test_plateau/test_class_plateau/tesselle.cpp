#include "tesselle.h"

Tesselle::Tesselle(int ident, int nombre, int couleur, int iplat, int jplat)
{
    id = ident;
    nb = nombre;
    coul = couleur;
    i = iplat;
    j = jplat;
}

ostream& operator<<(ostream &sortie, Tesselle &d) { // opérateur <<
    sortie << "[" << " " << d.nb << " " << d.i << " " << d.j << " " << "]";
    return sortie;
}

void Tesselle::SetPosition(int i, int j)
{

}

void Tesselle::IncrNb()
{

}

void Tesselle::IncrCoul()
{

}

int Tesselle::GetScore()
{
    return nb;
}

int Tesselle::GetI()
{
    return i;
}

int Tesselle::GetJ()
{
    return j;
}

void Tesselle::Fusion(Tesselle &t)
{

}

