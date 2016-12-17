#include "head.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string maska;
    F_Poisk* fff = new F_Poisk();

    if (argc > 1)
        maska = argv[1];
    else
    {
        cout << "Vvod disk, catalog, and/or maska faila ([drive:][ras]maska): ";
        cin >> maska;
        cout << endl;
        if (!maska.length())
            return 1;
    }

    fff->setmaska(maska);

    while (fff->hasMore())
        fff->next()->show();

    return 0;
}
