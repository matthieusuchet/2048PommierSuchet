#ifndef TESSELLE_H
#define TESSELLE_H

#include <QObject>

class Tesselle : public QObject
{
    Q_OBJECT
public:
    explicit Tesselle(QObject *parent, int ident, int nombre, int couleur, int iplat, int jplat);

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

signals:

};

#endif // TESSELLE_H
