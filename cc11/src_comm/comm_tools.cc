
#include "comm_include.h"

namespace CC11Comm {
    void CC11Printf(const char* s) {
        while (*s) {
            if (*s == '%' && *++s != '%') {
                //�䳤������������, �����и�ʽ���ַ�����
                assert(false);
                throw runtime_error("invalid format string: missing arguments");
            }
            cout << *s++;
        }
    }
}
