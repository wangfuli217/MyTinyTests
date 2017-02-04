
#include <iostream>
using namespace std;

#define FUNC_ROUTINE_MACRO(pos) (cout << pos << " " << __func__ << endl << endl)
#define ENTER_FUNC FUNC_ROUTINE_MACRO("Enter")
#define EXIT_FUNC FUNC_ROUTINE_MACRO("Exit")

class MyBase {
public:
    MyBase() { cout << "MyBase()" << endl; }
    MyBase(int i) { cout << "MyBase(int)" << endl;}
    MyBase(int i, double d) { cout << "MyBase(int, double)" << endl; }

public:
    void PrintMyBase() {
        cout << "Call My Base, a_ = " << a_ << endl;
    }

private:
    int a_ { 10 };
};

class InheritOne : MyBase {
public:
    InheritOne() : MyBase() { cout << "InheritOne()" << endl; }
    InheritOne(int i) : MyBase(i) { cout << "InheritOne(int)" << endl; }
    InheritOne(int i, double d) : MyBase(i, d) { cout << "InheritOne(int, double)" << endl; }

public:
    using MyBase::PrintMyBase;

    void PrintOne() {
        PrintMyBase();
        cout << "Inherit One from My Base, b_ = " << b_ << endl;
    }

private:
    char b_ {'b'};
};

class InheritTwo : MyBase {
public:
    using MyBase::MyBase;   //�̳л���Ĺ��캯��

public:
    void PrintTwo() {
        cout << "Inherit Two from My Base, c_ = " << c_ << endl;
    }
private:
    double c_{ 3.3f };
};
/////////////////////// Test Case /////////////////////////
void TestCase1()
{
    ENTER_FUNC;

    InheritOne aOne;
    aOne.PrintOne();
    
    // Ĭ��Ϊprivate�̳У���������Ķ����޷�ֱ�ӷ��ʻ���ĳ�Ա�ͷ���, ���������public����
    // ʹ��using�ؼ����������ֱ�ӷ���
    aOne.PrintMyBase();

    EXIT_FUNC;
}

void TestCase2()
{
    ENTER_FUNC;

    InheritOne aOne = InheritOne();
    InheritOne bOne = InheritOne(10);
    InheritOne cOne = InheritOne(20, 2.2f);

    EXIT_FUNC;
}

void TestCase3()
{
    ENTER_FUNC;

    InheritTwo aTwo = InheritTwo();
    InheritTwo bTwo = InheritTwo(11);
    InheritTwo cTwo = InheritTwo(21, 3.4f);
    cTwo.PrintTwo();

    EXIT_FUNC;
}
/////////////////////// Test Case /////////////////////////

int main()
{
    TestCase1();
    TestCase2();
    TestCase3();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}
