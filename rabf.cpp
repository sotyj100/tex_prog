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
int pos = 0;
