
#include "comm_include.h"

//�䳤ģ�������
template <typename... Elements> 
class MyTuple;

//�䳤ģ��ĵݹ��ػ�
template <typename Head, typename... Tail>
class MyTuple<Head, Tail...> : private MyTuple<Tail...> {
    Head head;
};
//�߽�����
template<> class MyTuple<>{};

//�����ͱ䳤ģ������
template <int ... A>
class NonTypeVariadicTemplate;

//�����ͱ䳤ģ��ĵݹ��ػ�
template <int first, int ... last>
class NonTypeVariadicTemplate<first, last...> {
public:
    static const long val = first * NonTypeVariadicTemplate<last...>::val;
};

//�߽�����
template<>
class NonTypeVariadicTemplate<> {
public:
    static const long val = 1;
};

void TestCase1() {
    ENTER_FUNC;

    MyTuple<int, char, double> mt;
    NonTypeVariadicTemplate<1, 10, 100> ntvt;
    cout << NonTypeVariadicTemplate<2, 5, 10, 15>::val << endl;

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
