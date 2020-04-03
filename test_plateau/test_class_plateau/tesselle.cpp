#include "tesselle.h"

Tesselle::Tesselle(int ident, int nombre, int couleur, int iplat, int jplat)
{
    id = ident;
    nb = nombre;
    coul = couleur;
    i = iplat;
    j = jplat;
}

Tesselle::Tesselle()
{
    Tesselle(0,0,0,0,0);
}

ostream& operator<<(ostream &sortie, Tesselle &d) { // opérateur <<
    sortie << d.nb; // << " " << " " << d.i << " " << d.j << " " << "]";
    return sortie;
}

bool operator==(const Tesselle &t1, const Tesselle &t2)
{
    return (t1.nb == t2.nb);
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

