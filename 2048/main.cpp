#include <iostream>
#include "plateau.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Plateau P;

    cout << P << endl;
    cout << "________" <<endl;

    P.move(1);

    cout << P << endl;
    cout << "________" <<endl;
    P.move(3);

    cout << P << endl;
    cout << "________" <<endl;



    return 0;
}


