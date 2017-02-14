
#include "comm_include.h"

union StaticMemberFunctionUnion {
    double d;

    static double GetG(){ return 9.8f; }    //����ռ���ֽ�
};

union StaticMemberUnion {
    
    int a;
    double b;

#if defined(_MSC_VER)

    //vs2015����֧�־�̬��Ա����, ��GCC�����ʧ��
    const static int c{1};  //����ռ���ֽ�
#endif
};


void TestCase1() {
    ENTER_FUNC;

    StaticMemberFunctionUnion s1{ 0.2f };
    cout << "s1 StaticMemberFunctionUnion.d " << s1.d << endl;
    cout << "s1 StaticMemberFunctionUnion.GetG " << s1.GetG() << endl;
    cout << "s1 StaticMemberFunctionUnion::GetG " << StaticMemberFunctionUnion::GetG() << endl;
    cout << "sizeof(StaticMemberFunctionUnion) " << sizeof(StaticMemberFunctionUnion) << endl;

    cout << "sizeof(StaticMemberUnion) " << sizeof(StaticMemberUnion) << endl;

    //NOTE: ����Union�ĳ�ʼ��
    //��ʵ������, û�й��캯����union��ʼ����Ϊ���������
    //��{0}��ʼ����Ŀ��Ч����������memset 0
    //��{��0}��ʼ��, Ŀ��Ч���ǽ����ø���һ����Ա, �������ĳ�Ա�൱��û�г�ʼ��
    //�ȽϺõ�����������ʽ�������캯��, Ҳ���߰ѵ�һ����Ա����Ϊռ���ֽ�������

    StaticMemberUnion s2{ 0 };
    cout << "s2 StaticMemberUnion.a " << s2.a << endl;
    cout << "s2 StaticMemberUnion.b " << s2.b << endl;
#if defined(_MSC_VER)
    cout << "s2 StaticMemberUnion.c " << s2.c << endl;
    cout << "s2 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

    StaticMemberUnion s3{ 1 };  
    cout << "s3 StaticMemberUnion.a " << s3.a << endl;
    cout << "s3 StaticMemberUnion.b " << s3.b << endl;
#if defined(_MSC_VER)
    cout << "s3 StaticMemberUnion.c " << s3.c << endl;
    cout << "s3 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

    StaticMemberUnion s4{ 2.2f };   
    cout << "s4 StaticMemberUnion.a " << s4.a << endl;
    cout << "s4 StaticMemberUnion.b " << s4.b << endl;
#if defined(_MSC_VER)
    cout << "s4 StaticMemberUnion.c " << s4.c << endl;
    cout << "s4 StaticMemberUnion::c " << StaticMemberUnion::c << endl;
#endif

    EXIT_FUNC;
}

union NonPodUnion {
    string s;
    int n;

    NonPodUnion() { new (&s) string(); }    //���з�POD��Աʱ, ��Ҫͨ��placement new����ʼ��
    ~NonPodUnion() { s.~string(); }
};

void TestCase2() {

    ENTER_FUNC;

    NonPodUnion t;
    cout << "sizeof(NonPodUnion) " << sizeof(NonPodUnion) << endl;

    EXIT_FUNC;
}

int main() {
    // test codes
    TestCase1();
    TestCase2();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}