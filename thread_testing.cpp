
#include <bits/stdc++.h>
using namespace std;

void func(int id, mutex* m) {

    m.lock();

    cout << "sending from thread: " << id << '\n';

    m.unlock();

}

int main() {

    mutex m;

    thread t1(func, 0, m);
    thread t2(func, 1, m);
    thread t3(func, 2, m);

    t1.join();
    t2.join();
    t3.join();

}
