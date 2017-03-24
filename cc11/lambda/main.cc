
#include "comm_include.h"

void TestCase1() {
    ENTER_FUNC;

    int a = 3, b = 4;

    auto var_print = [&] {
        cout << "a = " << a << ", b = " << b << endl;
    };

    auto sum1 = [](int x, int y)->int {return x + y; };
    cout << sum1(a, b) << endl;

    auto sum2 = [&] {return a + b; };
    cout << sum2() << endl;

    auto sum3 = [=, &b] {return a + b; };   //��ֵ����ʱ, �Ƕ����ʱ��ֱ�Ӵ�ֵ? 
    a = 5;
    b = 10;
    cout << sum3() << endl;
    var_print();

    auto sum4_plusplus = [=, &b]() {
        b++;
        return a + b;
    };
    cout << sum4_plusplus() << endl;
    var_print();

    auto sum5_plusplus = [=, &b]() mutable {
        a++;    //��mutable�����޸İ�ֵ�������, ����Ȼֵ���ᴫ��. mutable����Ӧ�����ڳ�Ա������
        b++;
        return a + b;
    };
    cout << sum5_plusplus() << endl;

    var_print();

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}