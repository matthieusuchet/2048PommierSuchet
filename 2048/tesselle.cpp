#include "tesselle.h"

Tesselle::Tesselle(int ident, int nombre, int couleur, int iplat, int jplat)
{
    id = ident;
    nb = nombre;
    indice_coul = 0;
    coul_texte = "#766e66"; // nombre écrit en gris
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

void Tesselle::SetPosition(int I, int J)
{
    i = I; j = J;
}

QString Tesselle::GetCouleur()
{
    return liste_coul[indice_coul];
}

QString Tesselle::GetCoulText()
{
    return coul_texte;
}

void Tesselle::IncrCoul()
{
    indice_coul++;
    if (nb >= 8) {
        coul_texte = "#f9f6f2"; // nombre écrit en blanc
    }
}

void Tesselle::IncrNb()
{
    nb = 2*nb;
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
    IncrNb();
    IncrCoul();
}

