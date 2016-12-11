#include "head.h"
#include <string>
#include <iostream>
#include <io.h>
using namespace std;

F_Poisk::F_Poisk(const string& maska)
{
    this->maska = maska;
    FindHandle = 0;
}

void F_Poisk::setmaska(const string& mask)
{
    maska = mask;
}

F_Name* F_Poisk::next()
{
    F_Name* res = cache;
    cache = NULL;
    return res;
}
