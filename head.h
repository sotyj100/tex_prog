#include <string>
#include <io.h>

using namespace std;

class F_Name
{
    std::string name;
    std::string ras;
public:
    F_Name();
    F_Name(const std::string& name, const std::string& ras);
    void show();
};

class F_Poisk
{
    F_Name* cache;
    F_Name* search(const string& maska);

    F_Poisk* subPoisk;

    string maska;
    intptr_t FindHandle;

    inline bool IsDirectory(const _finddata_t &FindData);
    bool compareToMask(const string& mask, const string& file);

public:
    F_Poisk() : FindHandle(NULL) {};

    F_Poisk(const string& maska);
    void setmaska(const string& mask);

    bool hasMore();
    F_Name* next();

};
