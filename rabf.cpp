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

bool F_Poisk::hasMore()
{
    cache = search(maska);
    if (this->cache != NULL)
        return true;
    else
        return false;
}

F_Name* F_Poisk::search(const string& maska)
{
    _finddata_t FindData;

    string defmaska = maska.substr(0, maska.find_last_of('\\') + 1) + "*.*";
    if (FindHandle == 0)
        FindHandle = _findfirst(defmaska.c_str(), &FindData);
    while (_findnext(FindHandle, &FindData) != -1L)
    {
        if ((FindData.name == string(".")) || (FindData.name == string("..")))
        {
            continue;
        }
        if (IsDirectory(FindData))
        {
            string newmaska = maska;
            newmaska.insert(maska.find_last_of('\\') + 1, string(FindData.name) + '\\');
            this->subPoisk = new F_Poisk(newmaska);
            while (this->subPoisk->hasMore())
                this->subPoisk->next()->show();
        }
        if (compareToMask(maska.substr(maska.find_last_of('\\') + 1), string(FindData.name)))
        {
            string name = string(FindData.name);
            string ras = defmaska.substr(0, defmaska.find_last_of('\\'));
            if (ras == "*.*")
                ras = "root";
            cache = new F_Name(name, ras);
            return cache;
        }
    }
    _findclose(FindHandle);
        return NULL;
}
