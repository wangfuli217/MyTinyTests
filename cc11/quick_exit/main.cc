
#include "comm_include.h"

#ifdef _MSC_VER
#include <windows.h>
#else
#define OutputDebugStringA(s) printf(s)
#endif

void openDevice() {
    OutputDebugStringA("device is opened.\n");
}

void resetDeviceStat() {
    OutputDebugStringA("device stat is reset.\n");
}

void closeDevice() {
    OutputDebugStringA("device is closed.\n");
}

class A {
public:
    ~A() {
        OutputDebugStringA("Destruct A.\n");
    }
};

int main() {

    A a;
#ifdef USE_EXIT
    atexit(closeDevice);
    atexit(resetDeviceStat);
    openDevice();
    exit(0);    
#else
    //default use quick exit
    at_quick_exit(closeDevice);
    at_quick_exit(resetDeviceStat);
    openDevice();
    quick_exit(0);
#endif
    //NOTE: ʵ������exit��quick_exitʵ�ֲ�û�в��, �����������������...

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}