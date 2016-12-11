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


