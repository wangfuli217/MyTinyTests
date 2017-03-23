
#ifndef COMM_INCLUDE_H_
#define COMM_INCLUDE_H_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <cstddef>
#include <atomic>
#include <thread>
#include <locale>
#if defined(_MSC_VER)
#include <cuchar>
#include <conio.h>
#endif
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


using namespace std;

#define FUNC_ROUTINE_MACRO(pos) (cout << pos << " " << __func__ << endl << endl)
#define ENTER_FUNC FUNC_ROUTINE_MACRO("Enter")
#define EXIT_FUNC FUNC_ROUTINE_MACRO("Exit")

#define VNAME(e) (#e)

#if defined(_MSC_VER)
#define ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS {\
    cout << "Please press any key to continue..." << endl;\
    _getch();\
}
#else
#define ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS (0)
#endif

#if defined(_MSC_VER)
#ifdef COMM_EXPORTS
#define SRC_COMM_DLL_API __declspec(dllexport)
#else
#define SRC_COMM_DLL_API __declspec(dllimport)
#endif
#else
#define SRC_COMM_DLL_API 
#endif

namespace CC11Comm {
    SRC_COMM_DLL_API void CC11Printf(const char*);

    template <typename T, typename... Args>
    void CC11Printf(const char* s, T val, Args... args) {
        //cout << endl << "invoke printf sizeof...(args) " << sizeof...(args) << endl;  //��ʹ�� `sizeof...` �����������
        while (*s) {
            if (*s == '%' && *++s != '%') {     //%�����һ����%���ַ�, ������Ҫȡ��һ���������
                                                //��ʵ������Ҫ��ʽ��ָ���������, ��Ϊ�䳤�������Ѿ�����
                cout << val;
                return CC11Printf(++s, args...);    //ȡ����һ������
            }
            cout << *s++;
        }

        //�ṩ�˶���Ĳ���
        assert(false);
        throw runtime_error("extra arguments provided to Printf");
    }

}

#endif