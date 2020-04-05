#include <iostream>
#include "plateau.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Plateau P;

    Tesselle t1(1,4,1,1,0);
    Tesselle t2(1,2,1,1,1);
    Tesselle t3(1,2,1,1,2);
    Tesselle t4(1,0,1,1,3);

    P.add_tesselle(t1);
    P.add_tesselle(t2);
    P.add_tesselle(t3);

    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();

    cout << P << endl;
    cout << "________" <<endl;

    P.move(1);

    cout << P << endl;
    cout << "________" <<endl;
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.move(3);

    cout << P << endl;
    cout << "________" <<endl;



    return 0;
}


