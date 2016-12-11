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
FIter* FIter_nn::next()
{
    FIter* res = cache;
    cache = NULL;
    return res;
}

void FIter_nn::setFileMask(const string& mask)
{
    fileMask = mask;
}

bool FIter_nn::hasMore()
{
    cache = search(fileMask);
    if (this->cache != NULL)
        return true;
    else
        return false;
}



FIter* FIter_nn::search(const string& fileMask)
{
    _finddata_t FindData;

    string defFileMask = fileMask.substr(0, fileMask.find_last_of('\\') + 1) + "*.*";
    if (FindHandle == 0)
        FindHandle = _findfirst(defFileMask.c_str(), &FindData);
    while (_findnext(FindHandle, &FindData) != -1L)
    {
        if ((FindData.name == string(".")) || (FindData.name == string("..")))
        {
            continue;
        }
        if (IsDirectory(FindData))
        {
            string newFileMask = fileMask;
            newFileMask.insert(fileMask.find_last_of('\\') + 1, string(FindData.name) + '\\');
            this->subIterator = new FIter_nn(newFileMask);
            while (this->subIterator->hasMore())
                this->subIterator->next()->show();
        }
        if (compareToMask(fileMask.substr(fileMask.find_last_of('\\') + 1), string(FindData.name)))
        {
            string name = string(FindData.name);
            string path = defFileMask.substr(0, defFileMask.find_last_of('\\'));
            if (path == "*.*")
                path = "root";
            cache = new FIter(name, path);
            return cache;
        }
    }
    _findclose(FindHandle);
        return NULL;
}


FIter::FIter() {};

FIter::FIter(const string& name, const string& path)
{
    this->name = name;
    this->path = path;
}

void FIter::show()
{
    cout << "File :" << name << endl;
    cout << "In catalog: " << path << endl << endl;
}
