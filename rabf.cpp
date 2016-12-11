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


inline bool F_Poisk::IsDirectory(const _finddata_t &FindData)
    {
        return ((FindData.attrib & _A_SUBDIR) != 0);
    }
bool F_Poisk::compareToMask(const string& mask, const string& file)
{
    int z = 0;
    for (int i = 0; i < mask.length(); i++)
        for (int j = z; j < file.length(); j++)
        {
            z = j;
            if (mask[i] == '*')
            {
                if (file[j] == '.')
                {
                    break;
                }
                else
                    continue;
            }
            else if ((mask[i] == '?') || (mask[i] == file[j]))
            {
                z++;
                break;
            }
            return false;
        }
    return true;
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
