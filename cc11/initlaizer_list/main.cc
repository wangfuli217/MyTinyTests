
#include "comm_include.h"
#include "ILPeople.h"
#include "ILMyData.h"

void TestCase1() {
    int a[] = { 1, 3, 5 };
    int b[] { 2, 4, 6 };

    //ͨ�� initialier_list<T> ʵ��
    vector<int> c{ 1, 3, 5 };
    map<int, double> d = { {1, 1.0f}, {2, 2.1f}, {3, 3.2f} };

    int *e = new int(1);
    delete e;
    double * f = new double{ 4.3f };
    delete f;
}

void TestCase2() {
    ILPeople p = { {"Garfield", boy}, {"HelloKitty", girl} };
}

void Func(initializer_list<int> iv) {
    for (auto i = iv.begin(); i != iv.end(); ++i)
    {
        cout << __func__ << ": " << *i << endl;
    }
}

void TestCase3() {
    ENTER_FUNC;

    Func({ 1, 3, 5, 7, 9 });

    EXIT_FUNC;
}

void TestCase4() {

    ENTER_FUNC;

    ILMyData d;
    d[{0, 2, 4}] = 1;
    d[{1, 3, 5}] = 2;
    d.Print();

    EXIT_FUNC;
}

vector<int> Func1_TestCase5() { return { 1,3,5 }; }
deque<double> Func2_TestCase5() { return{ 2.2f,4.4f,6.6f }; }

void TestCase5() {
    ENTER_FUNC;

    const vector<int>& v1 = Func1_TestCase5();  // const T& ������ֵ, ������������
    for (auto i = v1.begin(); i != v1.end(); ++i)
    {
        cout << "const vector<int>&: " << *i << endl;
    }

    deque<double>&& d1 = Func2_TestCase5();     // T&& ������ֵ, ������������
    for (auto i = d1.begin(); i != d1.end(); ++i)
    {
        cout << "deque<double>&&: " << *i << endl;
    }

    deque<double> d2 = Func2_TestCase5();   //��������
    for (auto i = d1.begin(); i != d1.end(); ++i)
    {
        cout << "deque<double>: " << *i << endl;
    }


    EXIT_FUNC;
}

int main()
{
    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}