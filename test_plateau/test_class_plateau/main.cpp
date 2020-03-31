#include <iostream>
#include "plateau.h"
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

    return 0;
}
