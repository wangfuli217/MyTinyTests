
#include "comm_include.h"

class TwoCstor {
public:
    TwoCstor() = default;
    TwoCstor(int i) : data_(i){}

    TwoCstor(const TwoCstor&) = delete; //ɾ��
    TwoCstor& operator = (const TwoCstor&);
private:
    int data_;
};
TwoCstor& TwoCstor::operator = (const TwoCstor&) = default; //�������ֿ��� ��ʽdefault

void TestCase1() {
    ENTER_FUNC;

    cout << "is_pod<TwoCstor>::value " << is_pod<TwoCstor>::value << endl;

    TwoCstor a;
    //TwoCstor b(a);    //��ɾ���˿�������

    EXIT_FUNC;
}

class ConvType {
public:
    ConvType(int i) {};
    ConvType(char c) = delete;  //������ʽ����ת��
};
void Func(int i){}
void Func(char c) = delete;

void TestCase2() {
    ENTER_FUNC;
    ConvType a(1);
    //ConvType b('a'); //�޷�������ɾ���ĺ���. ����ɾ��, ����ʽת��������int�汾

    Func(1);
    //Func('a');//�޷�������ɾ���ĺ���. ����ɾ��, ����ʽת��������int�汾

    EXIT_FUNC;
}

class NoHeadAlloc {
public:
    void * operator new(std::size_t) = delete;  //��ֹnew������, ֻ��ջ�Ϸ���
};

class NoStackAlloc {
public:
    ~NoStackAlloc() = delete;   //��ֹ����, ֻ��ͨ��placement new��ʼ��

    void Print() { cout << "NoStackAlloc" << endl; }
};

void TestCase3() {
    ENTER_FUNC;

    NoHeadAlloc a;
    //NoHeadAlloc *b = new NoHeadAlloc;

    //ɾ��������, ���ǲ�����ջ��ʹ��, Ҳ����ʹ��new/delete����(������new��������delete, �ʻ��ڴ�й¶), ֻ��placement new��ȫʹ��
    //NoStackAlloc c;
    void *p = new void*[sizeof(NoStackAlloc)];
    NoStackAlloc* pN = new (p) NoStackAlloc();
    pN->Print();
    delete [] p;

    NoStackAlloc* d = new NoStackAlloc;
    d->Print();
    //delete d; //���ܵ���delete, �ڴ�й¶
    

    EXIT_FUNC;
}

int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();


    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}