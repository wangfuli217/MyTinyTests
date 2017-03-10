
#include "comm_include.h"

void action1(int& e) {
    e *= 2;
}
void action2(int& e) {
    cout << e << '\t';
}

void TestCase1() {
    ENTER_FUNC;
    
    int arr[5] = { 1,2,3,4,5 };

    //ģ�����ͨ������ָ��Ļص���ʵ�ֵ���
    for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action1);
    for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), action2);
    cout << endl;
    EXIT_FUNC;
}

void TestCase2() {
    ENTER_FUNC;

    int arr[5] = { 1,2,3,4,5 };

    //���ڷ�Χ��for
    for (int& e : arr)
    {
        e *= 2;
    }
    for (int& e : arr)
    {
        cout << e << '\t';
    }
    cout << endl;
    for (const int& e : arr)
    {
        cout << e << '\t';
    }
    cout << endl;
    for (int e : arr)
    {
        cout << e << '\t';
    }
    cout << endl;
    for (auto e : arr)
    {
        cout << e << '\t';
    }
    cout << endl;
    for (auto& e : arr)
    {
        e *= 2;
    }
    for (auto& e : arr)
    {
        cout << e << '\t';
    }
    cout << endl;


    EXIT_FUNC;
}

void TestCase3() {
    ENTER_FUNC;

    vector<int> v = { 1,2,3,4,5 };
    for (auto i = v.begin(); i != v.end(); ++i)
    {
        cout << *i << '\t'; //i�ǵ�����
    }
    cout << endl;
    for (auto& e : v)
    {
        e *= 2; //e�ǽ�����֮��Ķ���
    }
    for (auto e: v)
    {
        cout << e << '\t';  //e�ǽ�����֮��Ķ���
    }
    cout << endl;
    for (auto e : v)
    {
        e *= 2; //e�ǽ�����֮��Ķ���, ����������, �ʲ����޸���ֵ
    }
    for (auto e : v)
    {
        cout << e << '\t';  //e�ǽ�����֮��Ķ���
    }
    cout << endl;
    
    EXIT_FUNC;
}

int main() {

    TestCase1();
    TestCase2();
    TestCase3();

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}