#include <iostream>
#include <windows.h>
using namespace std;

class Event
{
    HANDLE hEvent;
public:
    Event() {
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    cout << endl << "ThreadCreateId: " << GetCurrentThreadId() << endl;
    }

    ~Event() {
    cout << endl << "ThreadDestoydId: " << GetCurrentThreadId() << endl;
        CloseHandle(hEvent);
    }


    void set() {
    SetEvent(hEvent);
    cout << endl << "ThreadDestoydId: " << GetCurrentThreadId() << endl;
    }

    void reset(){
    ResetEvent(hEvent);
    }

    void wait() {
   cout << endl << "WaitThreadId: " << GetCurrentThreadId() << endl;
    WaitForSingleObject(hEvent, INFINITE);
    }

};
class CriticalSection : public Lock {
private:
    CRITICAL_SECTION Crit_Sect;
public:
    CriticalSection() {
    InitializeCriticalSection(&Crit_Sect);
    }

    ~CriticalSection() {
    }

void lock() {
    EnterCriticalSection(&Crit_Sect);
    }

    void unlock() {
    LeaveCriticalSection(&Crit_Sect);
    }
};

class Semaphor : public Lock {
private:
    int count_m;
    int count;
    CriticalSection *tCrit_Sect;
    Event *event;
public:
    Semaphor(int count_m) : count_m(count_m), count(0){
    tCrit_Sect = new CriticalSection();
    event = new Event();
    }

    ~Semaphor(){
    delete event;
    delete tCrit_Sect;
    }

int main()
{

}
