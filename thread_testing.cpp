
#include <bits/stdc++.h>
using namespace std;

void func(vector<int>* v) {

    for (int n : *v) {
        cout << n << " ";
    }
    cout << endl;

}

int main() {

    vector<int> v = {1, 2, 3};

    thread t1(func, &v);
    t1.join();

}
