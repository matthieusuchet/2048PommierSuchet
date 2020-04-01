#include <iostream>
#include "plateau.h"
#include <vector>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Plateau P;

    cout << P << endl;
    cout << "________" <<endl;
    P.add_tesselle_random();
    P.add_tesselle_random();
    P.add_tesselle_random();
    cout << P << endl;
    return 0;
}


