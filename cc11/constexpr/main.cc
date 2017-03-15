
#include "comm_include.h"

constexpr int GetConstexpr() { 
    static_assert(0 == 0, "test assert failed.");
    return 1; 
}

class MyConstexprType {
public:
    constexpr MyConstexprType(int x) : val_(x) {}
    constexpr int val() { return val_; }    //�����������������ϵı���, val_ �������ڳ�����Ա����
private:
    int val_;   
};

void TestCase1() {
    ENTER_FUNC;

    int arr[GetConstexpr()] = { 0 };
    constexpr MyConstexprType mt1{ 10 };
    constexpr MyConstexprType mt2{ 5 };
    cout << mt1.val() << endl;
    cout << mt2.val() << endl;

    EXIT_FUNC;
}

//ʹ�ó������ʽ����, ����ʱ�Ƶ���쳲��������е�ֵ
constexpr int Fibonacci(int n) {
    return (n == 1) ? 1 : ((n == 2) ? 1 : Fibonacci(n - 1) + Fibonacci(n - 2));
}

//ʹ��ģ��Ԫ��̵ķ�ʽ������ʱ�Ƶ���쳲��������е�ֵ
template <long num>
struct FibonacciT {
    static const long val = FibonacciT<num - 1>::val
        + FibonacciT<num - 2>::val;
};
template<> struct FibonacciT<2> { static const long val = 1; };
template<> struct FibonacciT<1> { static const long val = 1; };
template<> struct FibonacciT<0> { static const long val = 0; };

void TestCase2() {
    ENTER_FUNC;

    int fib[] = {   
        Fibonacci(11), Fibonacci(12), Fibonacci(13),
        Fibonacci(14), Fibonacci(15), Fibonacci(16)
    };

    int fib2[] = {
        FibonacciT<11>::val, FibonacciT<12>::val,
        FibonacciT<13>::val, FibonacciT<14>::val,
        FibonacciT<15>::val, FibonacciT<16>::val
    };

    for (auto i : fib) {
        cout << i << endl;
    }
    for (auto i : fib2) {
        cout << i << endl;
    }
    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}