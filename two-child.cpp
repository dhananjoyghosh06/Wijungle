#include <bits/stdc++.h>
using namespace std;

int main() {
    int sv= 0;
    int x = fork();

    if (x == 0) {
        cout << "Child 1 - x: " << getpid() << ", shared_variable: " << sv << endl;
        sv = 10;
        cout << "Child 1 - Modified shared_variable: " << sv << endl;
    } else {
        int y = fork();
        if (y == 0) {
            cout << "Child 2 - y: " << getpid() << ", shared_variable: " << sv <<endl;
            shared_variable = 20;
            cout << "Child 2 - Modified shared_variable: " << sv<<endl;
        } else {
            wait(NULL);
            cout << "Parent process - shared_variable: "<< sv <<endl;
        }
    }

    return 0;
}
