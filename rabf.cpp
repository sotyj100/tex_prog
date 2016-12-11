#include "head.h"
#include <io.h>
#include <string>
#include <iostream>

using namespace std;

Poisk_failov::Poisk_failov(const string& fileMask)
{
    this->fileMask = fileMask;
    FindHandle = 0;
}

inline bool Poisk_failov::IsDirectory(const _finddata_t &FindData)
    {
        return ((FindData.attrib & _A_SUBDIR) != 0);
    }
bool Poisk_failov::compareToMask(const string& mask, const string& file)
{
    int pos = 0;
    for (int i = 0; i < mask.length(); i++)
        for (int j = pos; j < file.length(); j++)
        {
            pos = j;
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
                pos++;
                break;
            }
            return false;
        }
    return true;
    }

void Poisk_failov::setFileMask(const string& mask)
{
    fileMask = mask;
}

F_Name* Poisk_failov::next()
{
    F_Name* res = cache;
    cache = NULL;
    return res;
}

bool Poisk_failov::hasMore()
{
    cache = search(fileMask);
    if (this->cache != NULL)
        return true;
    else
        return false;
}

F_Name* Poisk_failov::search(const string& fileMask)
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
            this->subPoisk = new Poisk_failov(newFileMask);
            while (this->subPoisk->hasMore())
                this->subPoisk->next()->show();
        }

        return NULL;
}

F_Name::F_Name() {};

F_Name::F_Name(const string& name, const string& path)
{
    this->name = name;
    this->path = path;
}

void F_Name::show()
{
    cout << "File :" << name << endl;
    cout << "In directory: " << path << endl << endl;
}
