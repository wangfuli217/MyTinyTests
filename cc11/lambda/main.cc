
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

    auto sum3 = [=, &b] {return a + b; };   //��ֵ����ʱ, �Ƕ����ʱ��ֱ�Ӵ�ֵ 
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

int z = 0;
float c = 0.0;
void TestCase2() {
    ENTER_FUNC;
    int x, y = 3;
    float a, b = 4.0;

    int success = 0;
    
    auto validate = [&]() -> bool {
        if ((x == y + z) && (a == b + c)) {
            return 1;
        }
        else {
            return 0;
        }
    };

    success += validate();

    y = 1024;
    b = 1e13;
    success += validate();

    cout << success << endl;
    EXIT_FUNC;
}

void TestCase3() {
    ENTER_FUNC;
    int times = 100;

    int x = 0;
    for (int i = 0; i < times; ++i)
    {
        x += 10;
    }

    const int y = [=] {   //��x��ȫ��ͬ�ĸ�ֵ, ����ʱֱ�ӵ���. �����ָ�ֵ���Է��ظ�const. 
        int val = 0;
        for (int i = 0; i < times; ++i)
        {
            val += 10;
        }
        return val;
    }();

    cout << x << ", " << y << endl;
    EXIT_FUNC;
}

void TestCase4() {
    ENTER_FUNC;

    int j = 12;
    auto by_val_lambda = [=] {return j + 1; };  //��ֵ����, ��������ʱ��������ֵ
    auto by_ref_lambda = [&] {return j + 1; };  //�����ô���, ��������ʱ��������ֵ

    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    j++;
    cout << "by_val_lambda: " << by_val_lambda() << endl;
    cout << "by_ref_lambda: " << by_ref_lambda() << endl;

    EXIT_FUNC;
}

void TestCase5() {
    ENTER_FUNC;

    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y) {return x + y; };
    cout << typeid(totalChild).name() << endl;

    typedef int(*allChild)(int, int);
    allChild p = totalChild;    //lambda����ֵ��ͬ������ĺ���ָ��(lambda�����в���)

    decltype(totalChild) p2 = totalChild;   
    //decltype(totalChild) p3 = p;  //������ָ�벻�ܸ�ֵ��lambda���ͱ���


    int val = 5;
    cout << val << endl;

    //Ĭ��lambdaΪconst, �������޸İ�ֵ����ı���
    //auto const_val_lambda = [=] {val = 3; };
    
    //����mutable���κ�, ȡ����const����, ���޸ĵ�ֵ���ᴫ��
    auto mutable_val_lambda = [=]() mutable { val = 6; };
    mutable_val_lambda();
    cout << val << endl;

    //�����ô���, �������ڲ��޸Ĳ����ֵ, ������. const���ε������ñ���. 
    auto const_ref_lambda = [&] { val = 7; };
    const_ref_lambda();
    cout << val << endl;


    EXIT_FUNC;
}

//��operator()��const�º���, ����lambda�ȼ�
//�º������ص�: �����г�ʼ״̬
class _functor {
public:
    int operator() (int x, int y) const { return x + y; }
};

void TestCase6() {
    ENTER_FUNC;

    int a = 3, b = 4;
    _functor f;
    cout << f(a, b) << endl;
    cout << [=] {return a + b; }() << endl;

    EXIT_FUNC;
}

class Tax {
private:
    float rate_;
    int base_;
public:
    Tax(float r, int b): rate_(r), base_(b){}
    float operator()(float money)const { return (money - base_) * rate_; }
};

void TestCase7() {
    ENTER_FUNC;
    Tax high(0.4, 30000);
    Tax middle(0.25, 20000);
    cout << "tax over 3w: " << high(37500) << endl;
    cout << "tax over 2w: " << middle(27500) << endl;

    float rate = 0.4;
    int base = 30000;
    auto tax_lambda = [&](int money) {
        return (money - base) * rate;
    };
    cout << "tax_lambda over 3w: " << tax_lambda(37500) << endl;
    rate = 0.25;
    base = 20000;
    cout << "tax_lambda over 2w: " << tax_lambda(27500) << endl;

    EXIT_FUNC;
}

vector<int> largeNums;
const int kBound = 10;
inline void LargeNumberFunc(int i) {
    if (i > kBound) {
        largeNums.push_back(i);
    }
}

class LNums {
public:
    LNums(int bound) : kBound_ {bound} {}

    void operator () (int i) const {
        if (i > kBound_) {
            largeNums.push_back(i);
        }
    }
private:
    const int kBound_{0};
};

void TestCase8() {
    ENTER_FUNC;

    vector<int> nums;
    for (int i = 0; i < 1000; ++i)
    {
        nums.push_back(rand() % 100);
    }

    largeNums.clear();

    //��ͳ��forѭ��
    for (auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        LargeNumberFunc(*itr);
    }
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + ����ָ�����
    for_each(nums.begin(), nums.end(), LargeNumberFunc);
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + �º���
    for_each(nums.begin(), nums.end(), LNums(kBound));
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    //for_each + lambda����
    for_each(nums.begin(), nums.end(), [](int i) {
        if (i > kBound) {
            largeNums.push_back(i);
        }
    });
    cout << "largeNums size: " << largeNums.size() << endl;
    largeNums.clear();

    EXIT_FUNC;
}

void TestCase9(){
    ENTER_FUNC;

    vector<int> nums;
    for (int i = 0; i < 1000; ++i)
    {
        nums.push_back(rand() % 100);
    }
    const int kVal = 10;

    for (auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        if (*itr == kVal) { 
            cout << "for find val: " << *itr << endl;
            break; 
        }
    }

    auto itr1 = find_if(nums.begin(), nums.end(), bind2nd(equal_to<int>(), kVal));
    if (itr1 == nums.end()) {
        cout << "find_if with bind2nd not found." << endl;
    }
    else {
        cout << "find_if with bind2nd find val: " << *itr1 << endl;
    }

    auto itr2 = find_if(nums.begin(), nums.end(), [kVal](int i) {
        return i == kVal;
    });
    if (itr2 == nums.end()) {
        cout << "find_if with lambda not found." << endl;
    }
    else {
        cout << "find_if with lambda find val: " << *itr2 << endl;
    }

    EXIT_FUNC;
}

void TestCase10() {
    ENTER_FUNC;
    vector<int> nums;
    for (int i = 0; i < 10; ++i)
    {
        nums.push_back(rand() % 100);
    }
    const int kPlusVal = 10;

    auto nums_print = [&nums] {
        for (auto& i : nums)
        {
            cout << i << "\t";
        }
        cout << endl;
    };

    nums_print();

    //��ͳ��for
    for (auto i = nums.begin(); i != nums.end(); ++i)
    {
        *i += kPlusVal;
    }
    nums_print();

    // plus<int>() �������˼ӷ����, ��û�иı�������е�����
    for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), kPlusVal));
    nums_print();

    // transform �Ὣ���д�뵽�����������ĵ�����
    transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), kPlusVal));
    nums_print();

    for_each(nums.begin(), nums.end(), [kPlusVal](int &i) {
        i += kPlusVal;
    });
    nums_print();

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

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
    return 0;
}