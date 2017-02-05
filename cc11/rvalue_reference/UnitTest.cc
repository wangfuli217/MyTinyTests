#include "UnitTest.h"
#include "HasPtrMem.h"
#include "Copyable.h"
#include "Moveable.h"

#include "comm_include.h"

UnitTest::UnitTest()
{
}


UnitTest::~UnitTest()
{
}

void UnitTest::Run()
{
    //TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();
}

void UnitTest::TestCase1()
{
    ENTER_FUNC;

    HasPtrMem::ClearSum();
    HasPtrMem a;
    HasPtrMem b(a);
    cout << *a.d_ << endl;
    cout << *b.d_ << endl;

    EXIT_FUNC;
}

void UnitTest::TestCase2()
{
    ENTER_FUNC;

    HasPtrMem::ClearSum();
    HasPtrMem a = HasPtrMem::GetTemp();

    EXIT_FUNC;
}

void UnitTest::TestCase3()
{
    ENTER_FUNC;

    cout << endl;

    cout << VNAME(is_reference<int>::value) << " " << is_reference<int>::value << endl;
    cout << VNAME(is_reference<int&>::value) << " " << is_reference<int&>::value << endl;
    cout << VNAME(is_reference<const int&>::value) << " " << is_reference<const int&>::value << endl;
    cout << VNAME(is_reference<int&&>::value) << " " << is_reference<int&&>::value << endl;
    cout << VNAME(is_reference<const int&&>::value) << " " << is_reference<const int&&>::value << endl;
    cout << VNAME(is_reference<int*>::value) << " " << is_reference<int*>::value << endl;

    cout << endl;

    cout << VNAME(is_rvalue_reference<int>::value) << " " << is_rvalue_reference<int>::value << endl;
    cout << VNAME(is_rvalue_reference<int&>::value) << " " << is_rvalue_reference<int&>::value << endl;
    cout << VNAME(is_rvalue_reference<const int&>::value) << " " << is_rvalue_reference<const int&>::value << endl;
    cout << VNAME(is_rvalue_reference<int&&>::value) << " " << is_rvalue_reference<int&&>::value << endl;
    cout << VNAME(is_rvalue_reference<const int&&>::value) << " " << is_rvalue_reference<const int&&>::value << endl;
    cout << VNAME(is_rvalue_reference<int*>::value) << " " << is_rvalue_reference<int*>::value << endl;
    
    cout << endl;

    cout << VNAME(is_lvalue_reference<int>::value) << " " << is_lvalue_reference<int>::value << endl;
    cout << VNAME(is_lvalue_reference<int&>::value) << " " << is_lvalue_reference<int&>::value << endl;
    cout << VNAME(is_lvalue_reference<const int&>::value) << " " << is_lvalue_reference<const int&>::value << endl;
    cout << VNAME(is_lvalue_reference<int&&>::value) << " " << is_lvalue_reference<int&&>::value << endl;
    cout << VNAME(is_lvalue_reference<const int&&>::value) << " " << is_lvalue_reference<const int&&>::value << endl;
    cout << VNAME(is_lvalue_reference<int*>::value) << " " << is_lvalue_reference<int*>::value << endl;

    EXIT_FUNC;
}

void UnitTest::TestCase4()
{
    ENTER_FUNC;

    cout << "Pass by lvalue " << endl;
    Copyable::AcceptLValue(Copyable::ReturnRValue());

    cout << "Pass by lvalue_reference " << endl;
    Copyable::AcceptLValueReference(Copyable::ReturnRValue());

    cout << "Pass by rvalue_reference " << endl;
    Copyable::AcceptRValueReference(Copyable::ReturnRValue());

    EXIT_FUNC;
}

void UnitTest::TestCase5()
{
    ENTER_FUNC;
    
    Copyable && a = Copyable::ReturnRValue();
    const Copyable && b = Copyable::ReturnRValue();

    EXIT_FUNC;
}

void UnitTest::TestCase6()
{
    ENTER_FUNC;

    HasPtrMem::ClearSum();
    HasPtrMem a;
    HasPtrMem b(move(a));   //触发移动构造函数
    //cout << *a.d_ << endl;    //a.d_已经被置空

    EXIT_FUNC;
}

void UnitTest::TestCase7()
{
    ENTER_FUNC;
    HasPtrMem::ClearSum();
    
    Moveable&& a = Moveable::GetTemp(); 
    cout << hex << "a HasPtrMem.d_ address " << a.hasPtrMem_.GetPtrAddress() << endl;

    Moveable b(move(a));    // a是一个右值引用, 但其本身是一个左值, 所以需要转换为右值引用以触发移动构造
    cout << hex << "b HasPtrMem.d_ address " << b.hasPtrMem_.GetPtrAddress() << endl;

    EXIT_FUNC;
}