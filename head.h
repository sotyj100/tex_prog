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
    FIter* cache;
    FIter* search(const string& fileMask);

    FIter_nn* subIterator;

    string fileMask;
    intptr_t FindHandle;

    inline bool IsDirectory(const _finddata_t &FindData);
    bool compareToMask(const string& mask, const string& file);

public:
    FIter_nn() : FindHandle(NULL) {};
    FIter_nn(const string& fileMask);
    void setFileMask(const string& mask);
    bool hasMore();
    FIter next();

};
