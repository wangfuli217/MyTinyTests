
#include "comm_include.h"

using my_uint32 = unsigned int;
typedef unsigned int my_uint32_t;

// using ����� ��������ģ��, �� typedef ����
template<typename T> using MapString = std::map<T, string>;

int main() {

    // test codes
    cout << is_same<my_uint32, my_uint32_t>::value << endl;

    MapString<int> numberedString;

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}