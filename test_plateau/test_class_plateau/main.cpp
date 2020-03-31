#include <iostream>
#include "plateau.h"
#include <vector>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Plateau P;
    P.Print();
    cout << "________" << endl;

    cout << P.est_vide() << endl;
    cout << P.est_plein() << endl;
    cout << "________" << endl;

    Tesselle T(1,2,3,1,1);
    P.add_tesselle(T);
    P.Print();
    cout << "________" << endl;

    P.add_tesselle_random();
    P.Print();
    cout << "________" << endl;

    P.init();
    P.Print();
    cout << "1________" << endl;

    P.init();
    P.Print();
    cout << "2________" << endl;

    P.init();
    P.Print();
    cout << "3________" << endl;

    P.reset_table();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.Print();
    cout << "15________" << endl;

    Tesselle D(1,1,1,1,1);
    vector <Tesselle> ligne(4,D);
    vector <vector <Tesselle>> tab(4,ligne); // création du tableau tab

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    };
    cout << "________" << endl;

    Tesselle A(1,1,1,12,14);
    tab[1][1] = A;

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    };


    return 0;
}
