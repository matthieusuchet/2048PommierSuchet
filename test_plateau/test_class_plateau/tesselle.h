#ifndef TESSELLE_H
#define TESSELLE_H


class Tesselle
{
public:
    Tesselle(int ident, int nombre, int couleur, int iplat, int jplat);

    void SetPosition(int i, int j);
    void IncrNb();
    void IncrCoul();
    int GetScore();
    int GetI();
    int GetJ();
    void Fusion(Tesselle &t);
private:
    int nb;
    int coul;
    int i;
    int j;
    int id;
};

#endif // TESSELLE_H
