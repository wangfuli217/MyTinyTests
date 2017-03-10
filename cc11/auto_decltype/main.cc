
#include "comm_include.h"

double foo() { return 1.1f; }

struct Str {
    int i;
} str1;

void TestCase1() {
    ENTER_FUNC;

    auto x = 1;
    auto y = foo();
    auto str2 = str1;

    cout << typeid(x).name() << endl;
    cout << typeid(y).name() << endl;
    cout << typeid(str2).name() << endl;

    EXIT_FUNC;
}

void TestCase2() {
    ENTER_FUNC;

    unsigned int a = UINT32_MAX;
    unsigned int b = 1;

    auto c = a + b;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = a+b, type: " << typeid(c).name() << ", value: " << c << endl;

    EXIT_FUNC;
}

template<typename T1, typename T2>
double Sum(T1 & t1, T2 & t2) {
    auto s = t1 + t2;
    cout << "t1 type: " << typeid(t1).name() << ", value: " << t1 << endl;
    cout << "t2 type: " << typeid(t2).name() << ", value: " << t2 << endl;
    cout << "s = t1+t2, type: " << typeid(s).name() << ", value: " << s << endl;
    return s;
}

void TestCase3() {
    ENTER_FUNC;

    int a = 3;
    long b = 4;
    float c = 1.0f, d = 2.3f;
    double e = 1.2f, f = 2.5f;

    auto h = Sum<int, long>(a, b);
    auto i = Sum<float, float>(c, d);
    auto j = Sum<double, double>(e, f);

    cout << (typeid(c) == typeid(d)) << endl;   //float == float
    cout << (typeid(j) == typeid(a)) << endl;   //double != int


    EXIT_FUNC;
}

//C++11�п��Ը�������ȫ��MAX/MIN
#define CC11_MAX(a, b) ({   \
auto _a = (a); \
auto _b = (b); \
(_a > _b) ? _a : _b; \
})

void TestCase4() {
    ENTER_FUNC;

#if !defined(_MSC_VER)
    //vs2015����Ȼ���Ա���ͨ������� CC11_MAX, ��ȴ���ܵ���, û������ʲô��˼..
    //��������:
    auto max1 = CC11_MAX(3, 4);
    auto max2 = CC11_MAX(3, 4.0f);

    cout << "max1 type: " << typeid(max1).name() << ", value: " << max1 << endl;
    cout << "max2 type: " << typeid(max2).name() << ", value: " << max2 << endl;
#endif

    EXIT_FUNC;
}


static int kBar = 3;
int & bar() { return kBar; }

void TestCase5() {
    ENTER_FUNC;

    int x = 10;
    int *y = &x;

    //ָ������
    auto *a = &x;
    auto b = &x;
    auto c = y;
    auto *d = y;
    cout << "a type: " << typeid(a).name() << ", is_reference: " << is_reference<decltype(a)>::value << ", value: " << a << endl;
    cout << "b type: " << typeid(b).name() << ", is_reference: " << is_reference<decltype(b)>::value << ", value: " << b << endl;
    cout << "c type: " << typeid(c).name() << ", is_reference: " << is_reference<decltype(c)>::value << ", value: " << c << endl;
    cout << "d type: " << typeid(d).name() << ", is_reference: " << is_reference<decltype(d)>::value << ", value: " << d << endl;

    //��������
    auto &e = x;
    auto &f = bar();
    cout << "e type: " << typeid(e).name() << ", is_reference: " << is_reference<decltype(e)>::value << ", value: " << e << endl;
    cout << "f type: " << typeid(f).name() << ", is_reference: " << is_reference<decltype(f)>::value << ", value: " << f << endl;

    //cv���Ʒ�
    //��������: ����ж������Ƿ����cv���Ʒ�? 
    const auto g = foo();
    const auto &h = foo();
    auto i = g;
    auto &j = g;
    auto k = h;
    auto &l = h;
    cout << "g type: " << typeid(g).name() << ", is_reference: " << is_reference<decltype(g)>::value 
        << ", value: " << g << endl;
    cout << "h type: " << typeid(h).name() << ", is_reference: " << is_reference<decltype(h)>::value 
        << ", value: " << h << endl;
    cout << "i type: " << typeid(i).name() << ", is_reference: " << is_reference<decltype(i)>::value 
        << ", value: " << i << endl;
    cout << "j type: " << typeid(j).name() << ", is_reference: " << is_reference<decltype(j)>::value 
        << ", value: " << j << endl;
    cout << "k type: " << typeid(k).name() << ", is_reference: " << is_reference<decltype(k)>::value 
        << ", value: " << k << endl;
    cout << "l type: " << typeid(l).name() << ", is_reference: " << is_reference<decltype(l)>::value 
        << ", value: " << l << endl;


    EXIT_FUNC;
}

class White{};
class Black{};

void TestCase6() {
    ENTER_FUNC;

    White a;
    Black b;

    cout << "a type: " << typeid(a).name() << ", hash_code: " << typeid(a).hash_code() << endl;
    cout << "b type: " << typeid(b).name() << ", hash_code: " << typeid(b).hash_code() << endl;

    White c;
    cout << "Same Type?" << endl;
    cout << "A and B? " << (int)(typeid(a).hash_code() == typeid(b).hash_code()) << " " << (int)(typeid(a) == typeid(b)) << endl;
    cout << "A and C? " << (int)(typeid(a).hash_code() == typeid(c).hash_code()) << " " << (int)(typeid(a) == typeid(c)) << endl;

    EXIT_FUNC;
}

void TestCase7() {
    ENTER_FUNC;

    int i;
    decltype(i) j;
    cout << "j type: " << typeid(j).name() << endl;

    float a;
    double b;
    decltype(a + b) c;
    cout << "c type: " << typeid(c).name() << endl;

    using test_size_t = decltype(sizeof(0));
    using ptrint_t = decltype((int*)0); //ָ������
    using ptrdiff_t = decltype((int*)0 - (int*)0);  //ָ��Ĳ�ֵ������Ϊint
    using nullptr_t = decltype(nullptr);
    using NULL_t = decltype(NULL);

    cout << "test_size_t type: " << typeid(test_size_t).name() << endl;
    cout << "ptrint_t type: " << typeid(ptrint_t).name() << endl;
    cout << "ptrdiff_t type: " << typeid(ptrdiff_t).name() << endl;
    cout << "nullptr_t type: " << typeid(nullptr_t).name() << endl;
    cout << "NULL_t type: " << typeid(NULL_t).name() << endl;

    EXIT_FUNC;
}

void TestCase8() {
    ENTER_FUNC;

    vector<int> vec;
    typedef decltype(vec.begin()) vectype;
    for (vectype i = vec.begin(); i != vec.end(); ++i)
    {
    }
    for (decltype(vec)::iterator i = vec.begin(); i != vec.end(); ++i)
    {
    }
    for (auto i = vec.begin(); i != vec.end(); ++i)
    {
    }

    vectype a;
    decltype(vec)::iterator b;
    auto c = vec.begin();

    cout << "vectype type: " << typeid(a).name() << endl;
    cout << "decltype(vec)::iterator type: " << typeid(b).name() << endl;
    cout << "auto c type: " << typeid(c).name() << endl;

    EXIT_FUNC;
}

//��������
enum {K1, K2, K3} anon_e;
union {
    decltype(anon_e) key;
    char* name;
} anon_u;
struct {
    int d;
    decltype(anon_u) id;
} anon_s[10];

void TestCase9() {
    ENTER_FUNC;

    //�����������͵Ŀ�����
    //��������÷�

    decltype(anon_s) a;
    cout << "decltype(anon_s) type: " << typeid(a).name() << endl;
    
    EXIT_FUNC;
}


//��Ӧ��TestCase3��Sum����
template<typename T1, typename T2>
void Sum2(T1 & t1, T2 & t2, decltype(t1 + t2) & s) {
    s = t1 + t2;
    cout << "t1 type: " << typeid(t1).name() << ", value: " << t1 << endl;
    cout << "t2 type: " << typeid(t2).name() << ", value: " << t2 << endl;
    cout << "s = t1+t2, type: " << typeid(s).name() << ", value: " << s << endl;
}

void TestCase10() { //����TestCase3 ����һ��
    ENTER_FUNC;

    int a = 3;
    long b = 5;
    float c = 1.0f, d = 2.0f;
    long e;
    float f;
    Sum2(a, b, e);
    Sum2(c, d, f);

    EXIT_FUNC;
}

//ͨ���������ñ��ʽ����ʽ�Ƶ�����, ʵ�ʲ�������ú���
int test_hash(char*);
void TestCase11() {
    ENTER_FUNC;

    map<char*, decltype(test_hash(nullptr))> dict_key;
    cout << "map<char*, decltype(test_hash(nullptr))> type: " << typeid(dict_key).name() << endl;

    EXIT_FUNC;
}

typedef double(*func)();
void TestCase12() {
    ENTER_FUNC;

    result_of<func()>::type f;
    cout << "result_of<func()>::type type: " << typeid(f).name() << endl;

    //TODO: ��������, result_of ��ʵ���о���

    EXIT_FUNC;
}

void TestCase13() {
    ENTER_FUNC;

    int i = 4;
    int arr[5] = { 0 };
    int *ptr = arr;
    struct S { double d; } s;

    int Overloaded(int);
    int Overloaded(char);
    int NoOverload(int);

    int && RvalRef();
    const bool Func(int);

    //����1, �������ŵı�Ƿ����ʽ�������Ա���ʱ��ʽ, �Ƶ������ʽ����Ӧ������
    //����ֱ��ʹ�����غ����ĺ�����
    decltype(arr) var1;
    decltype(ptr) var2;
    decltype(s.d) var3;
    decltype(Overloaded(10)) var4;
    //decltype(Overloaded) var5;    //���벻��, ��֧�����صĺ���
    decltype(NoOverload) var6;
    cout << "var1 type: " << typeid(var1).name() << endl;
    cout << "var2 type: " << typeid(var2).name() << endl;
    cout << "var3 type: " << typeid(var3).name() << endl;
    cout << "var4 type: " << typeid(var4).name() << endl;
    cout << "var6 type: " << typeid(var6).name() << endl;

    //����, ����2, ����ֵ, �Ƶ���T&&
    //��������һ��Ҫ��ʼ��, ��������˱���
    decltype(RvalRef()) var7 = 1;
    cout << "var7 type: " << typeid(var7).name() << ", is_rvalue_reference: " << is_rvalue_reference<decltype(RvalRef())>::value << endl;

    //����, ����3, ��ֵ, �Ƶ�Ϊ���͵���ֵ����
    //��������һ��Ҫ��ʼ��, ��������˱���
    decltype(true ? i : i) var8 = i;
    decltype((i)) var9 = i;
    decltype(++i) var10 = i;
    decltype(arr[3]) var11 = i;
    decltype(*ptr) var12 = i;
    decltype("lval") var13 = "lval";    //����ֵ����Ϊ��ֵ
    cout << "var8 type: " << typeid(var8).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype(true ? i : i)>::value << endl;
    cout << "var9 type: " << typeid(var9).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype((i))>::value << endl;
    cout << "var10 type: " << typeid(var10).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype(++i)>::value << endl;
    cout << "var11 type: " << typeid(var11).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype(arr[3])>::value << endl;
    cout << "var12 type: " << typeid(var12).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype(*ptr)>::value << endl;
    cout << "var13 type: " << typeid(var13).name() << ", is_lvalue_reference: " << is_lvalue_reference<decltype("lval")>::value << endl;

    //����, ����4, �Ƶ�Ϊ������
    decltype(1) var14;
    decltype(i++) var15;
    decltype((Func(1))) var16;
    cout << "var14 type: " << typeid(var14).name() << endl;
    cout << "var15 type: " << typeid(var15).name() << endl;
    cout << "var16 type: " << typeid(var16).name() << endl;


    //CV���Ʒ�
    const int ci = 0;
    const struct si { int i; } si1;
    cout << "decltype(ci) is_const: " << is_const<decltype(ci)>::value << endl;
    cout << "decltype(si1) is_const: " << is_const<decltype(si1)>::value << endl;
    cout << "decltype(si1.i) is_const: " << is_const<decltype(si1.i)>::value << endl;   //��Ա��������const


    EXIT_FUNC;
}


int main() {

    // test codes
    TestCase1();
    TestCase2();
    TestCase3();
    TestCase4();
    TestCase5();
    TestCase6();
    TestCase7();
    TestCase8();
    TestCase9();
    TestCase10();
    TestCase11();
    TestCase12();
    TestCase13();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}