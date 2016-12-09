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
new izmeneniya
