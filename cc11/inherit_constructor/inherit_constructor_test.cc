
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


class MyBase2 {
public:
    MyBase2() { cout << "MyBase2()" << endl; }
    MyBase2(int i) { cout << "MyBase2(int)" << endl; }
    MyBase2(int i, double d) { cout << "MyBase2(int, double)" << endl; }

public:
    void PrintMyBase2() {
        cout << "Call My Base2" << endl;
    }

};

class InheritThree : MyBase2, MyBase {  //����˳��Ӱ��̳й��캯�����õ�˳��, �ȼ̳е����ȵ���
public:

    //�˴��Ĺ��캯���̳�����, ����Ӱ�����˳��
    using MyBase2::MyBase2;
    using MyBase::MyBase;
    
    //����˼̳й��캯��ʱ�ĳ�ͻ, �����ǻ�Ĭ�ϵ������������Ĭ�Ϲ��캯��, ������ʽ�����ƶ��İ汾
    InheritThree() { cout << "InheritThree()" << endl; }
    InheritThree(int i) { cout << "InheritThree(int)" << endl; }
    InheritThree(int i, double d) : MyBase(i, d), MyBase2(i, d) {   //�����д�ĳ�ʼ��˳�򲢲�Ӱ����������ʱ�ĳ�ʼ��˳��
        cout << "InheritThree(int, double)" << endl; 
    }
};

class MyBase3 {
public:
    MyBase3(int i) { cout << "MyBase3(int)" << endl; }
};
class InheritFour : MyBase3 {
public:
    using MyBase3::MyBase3;
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

void TestCase4()
{
    ENTER_FUNC;
    InheritThree aThree = InheritThree();
    InheritThree bThree = InheritThree(12);
    InheritThree cThree = InheritThree(22, 3.5f);

    EXIT_FUNC;
}

void TestCase5()
{
    ENTER_FUNC;
    InheritFour aFour = InheritFour(23);
    //InheritFour bFour = InheritFour();  //û��Ĭ�Ϲ��캯��, �޷�ͨ������
    EXIT_FUNC;
}
/////////////////////// Test Case /////////////////////////

int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();

#if defined(_MSC_VER)
    //wait before return
    cout << "Please press any key to continue..." << endl;
    char a;
    cin >> a;
#endif

}
