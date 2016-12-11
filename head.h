#include <string>
#include <io.h>

using namespace std;

class FIter
{
    std::string name;
    std::string path;
public:
    FIter();
    FIter(const std::string& name, const std::string& path);
    void show();
};


class FIter_nn
{
    FileItem* cache;
    FileItem* search(const string& fileMask);

    FileIterator* subIterator;

    string fileMask;
    intptr_t FindHandle;

    inline bool IsDirectory(const _finddata_t &FindData);
    bool compareToMask(const string& mask, const string& file);

public:
    FileIterator() : FindHandle(NULL) {};
    FileIterator(const string& fileMask);
    void setFileMask(const string& mask);
    bool hasMore();
    FileItem* next();

};
