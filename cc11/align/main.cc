
#include "comm_include.h"

struct HowManyBytes {
    char a;
    int b;
};

void TestCase1() {
    ENTER_FUNC;
    cout << "sizeof(char): " << sizeof(char) << endl;
    cout << "sizeof(int): " << sizeof(int) << endl;
    cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << endl;

    cout << endl;
    cout << "offset of char a: " << offsetof(HowManyBytes, a) << endl;
    cout << "offset of int b: " << offsetof(HowManyBytes, b) << endl;

    EXIT_FUNC;
}

struct ColorVector {
    double r;
    double g;
    double b;
    double a;
};

struct alignas(32) ColorVector32 {
    double r;
    double g;
    double b;
    double a;
};

struct Completed{};

void TestCase2() {
    ENTER_FUNC;
    cout << "alignof(ColorVector): " << alignof(ColorVector) << endl;
    cout << "sizeof(ColorVector): " << sizeof(ColorVector) << endl;

    cout << "alignof(ColorVector32): " << alignof(ColorVector32) << endl;
    cout << "sizeof(ColorVector32): " << sizeof(ColorVector32) << endl;

    cout << "alignof(Completed): " << alignof(Completed) << endl;
    cout << "sizeof(Completed): " << sizeof(Completed) << endl;

    int a;
    long long b;
    auto& c = b;
    char d[1024];
#ifndef _MSC_VER
    //NOTE: VS2015��alignof��Ȼ��֧�ֱ�����Ϊ����?!
    cout << "alignof(int a): " << alignof(a) << endl;
    cout << "alignof(long long b): " << alignof(b) << endl;
    cout << "alignof(auto& c = b): " << alignof(c) << endl;
    cout << "alignof(char d[1024]): " << alignof(d) << endl;
#endif
    cout << "alignof(int): " << alignof(int) << endl;
    cout << "alignof(long long): " << alignof(long long) << endl;
    cout << "alignof(char [1024]): " << alignof(char[1024]) << endl;

    alignas(double) char e;
    alignas(alignof(double)) char f;
#ifndef _MSC_VER
    cout << "alignof(e): " << alignof(e) << endl;
    cout << "alignof(f): " << alignof(f) << endl;
#endif // _MSC_VER

#ifdef _MSC_VER
    //G++ 4.9�汾ò�Ʋ�����
    cout << "alignof(std::max_align_t): " << alignof(std::max_align_t) << endl;
#endif
    EXIT_FUNC;
}

//�̶�����������
template <typename T>
class FixedCapacityArray {
public:
    void push_back(T t) {
        //��data�м���t����
    }
    //...
    char alignas(T) data[1024] = { 0 }; //ʵ����: ��G++��alignas(T)��������, ��vs2015���޷��鿴�����Ķ���
};

void TestCase3() {
    ENTER_FUNC;
    FixedCapacityArray <char> arrCh;
    cout << "alignof(char): " << alignof(char) << endl;
    cout << "alignof(FixedCapacityArray <char>): " << alignof(FixedCapacityArray <char>) << endl;
#ifndef _MSC_VER
    cout << "alignof(arrCh): " << alignof(arrCh) << endl;
    cout << "alignof(arrCh.data): " << alignof(arrCh.data) << endl;
#endif
    
    FixedCapacityArray <ColorVector32> arrCV;
    cout << "alignof(ColorVector32): " << alignof(ColorVector32) << endl;
    cout << "alignof(FixedCapacityArray <ColorVector32>): " << alignof(FixedCapacityArray <ColorVector32>) << endl;
#ifndef _MSC_VER
    cout << "alignof(arrCV): " << alignof(arrCV) << endl;
    cout << "alignof(arrCV.data): " << alignof(arrCV.data) << endl;
#endif

    EXIT_FUNC;
}


int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}