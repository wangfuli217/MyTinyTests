
#include "comm_include.h"

void TestCase1() {  //unique_ptr
    ENTER_FUNC;

    unique_ptr<int> up1(new int(11));
    unique_ptr<int> up2{ new int(12) };
    //unique_ptr<int> up3 = up2;  //unique_ptr���ܿ�������, Ҳ���ܸ�weak_ptr/shared_ptr����
    cout << *up1 << endl;
    cout << *up2 << endl;

    unique_ptr<int> up3 = move(up1);
    cout << *up3 << endl;
    //cout << *up1 << endl;   //up1�Ѳ���������Ч�ڴ�, �ᱨ��
    up1.reset();    //���������Ч��ָ�����
    up1.reset();    //�����ظ�����

    up3.reset();
    //cout << *up3 << endl;   //up3�Ѳ���������Ч�ڴ�, �ᱨ��

    EXIT_FUNC;
}

static void CheckSharedPtr(weak_ptr<int> & wp) {
    shared_ptr<int> sp = wp.lock(); //wp.lock(): ��wpָ���shared_ptr��ָ����ڴ���Ч, �򷵻�shared_ptr, ���򷵻�nullptr
    if (sp != nullptr) {
        cout << "still " << *sp << endl;
    }
    else {
        cout << "pointer is invalid." << endl;
    }
}

void TestCase2() {  //shared_ptr, weak_ptr
    ENTER_FUNC;

    shared_ptr<int> sp1{ new int(22) };
    shared_ptr<int> sp2 = sp1;  
    weak_ptr<int> wp1 = sp1;

    cout << *sp1 << endl;
    cout << *sp2 << endl;
    CheckSharedPtr(wp1);

    *sp1 += 1;  //sp1��sp2ָ�����ͬһ���ڴ�, ���޸�*sp1�ȼ����޸�*sp2
    cout << *sp1 << endl;
    cout << *sp2 << endl;

    sp1.reset();    //ָ����ڴ�����ü�����1
    cout << *sp2 << endl;
    CheckSharedPtr(wp1);

    sp2.reset();
    CheckSharedPtr(wp1);    //ֱ����ָ����ڴ����ü�����Ϊ0, ��������shared_ptr����, weak_ptr���޷�תΪ��Ч��shared_ptr

    EXIT_FUNC;
}

void TestCase3() {
    ENTER_FUNC;

//#ifndef __GUNC__  //clang also defined __GUNC__
#if defined(__clang__) || defined(_MSC_VER)
    pointer_safety ps = get_pointer_safety();
    switch (ps) {
    case pointer_safety::strict:
        cout << "pointer_safety value: " << (int)ps << ", support minimum GC." << endl;
        break;
    case pointer_safety::preferred:
    case pointer_safety::relaxed:
    default:
        cout << "pointer_safety value: " << (int)ps << ", does not support minimum GC." << endl;
        break;
    }

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