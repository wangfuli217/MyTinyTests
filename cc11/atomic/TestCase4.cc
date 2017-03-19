
#include "comm_include.h"

atomic<int> a{ 0 };
atomic<int> b{ 0 };

int ValueSet(int) {
    int t = 1;
    a.store(t, memory_order_relaxed);
    b.store(2, memory_order_release);   //��֤����֮ǰ��ԭ��д�����������

    return 0;
}

int Observer(int) {
    while (b.load(memory_order_acquire) != 2) { //��֤����ִ�����, ����ִ�к�����ԭ�Ӷ�����

    }
    cout << "(" << a.load(memory_order_relaxed) << ", " << b << ")" << endl;

    return 0;
}

void TestCase4() {
    ENTER_FUNC;

    thread t1(ValueSet, 0);
    thread t2(Observer, 0);

    t1.join();
    t2.join();

    cout << "Got (" << a << ", " << b << ")" << endl;

    EXIT_FUNC;
}