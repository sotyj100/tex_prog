#include "head.h"
#include <string>
#include <iostream>
#include <io.h>
using namespace std;

FIter_nn::FIter_nn(const string& fileMask)
{
    this->fileMask = fileMask;
    FindHandle = 0;
}

inline bool FIter_nn::IsDirectory(const _finddata_t &FindData)
    {
        return ((FindData.attrib & _A_SUBDIR) != 0);
}

bool FIter_nn::compareToMask(const string& mask, const string& file)
{
int ab = 0;

for (int i = 0; i < mask.length(); i++)
        for (int j = ab; j < file.length(); j++)
        {
            ab = j;
            if (mask[i] == '*')
            {
                if (file[j] == '.')
                {
                    break;
                }
                else
                    continue;
            }
            else if ((mask[i] == '?') || (mask[i] == mask[j]))
            {
                ab++;
                break;
            }
            return false;
        }
    return true;
}
