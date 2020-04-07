#include "tesselle.h"

Tesselle::Tesselle(int nombre, int indice_couleur, int iplat, int jplat)
{
    nb = nombre;
    indice_coul = indice_couleur;
    coul_texte = "#766e66"; // nombre écrit en gris
    i = iplat;
    j = jplat;
}

Tesselle::Tesselle()
{
    Tesselle(0,0,0,0);
}

ostream& operator<<(ostream &sortie, Tesselle &d) { // opérateur <<
    sortie << d.nb; // << " " << " " << d.i << " " << d.j << " " << "]";
    return sortie;
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

void Tesselle::Fusion()
{
    nb = 2*nb;
    IncrCoul();
}

