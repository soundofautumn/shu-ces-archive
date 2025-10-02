#include <string>
#include <iostream>

using namespace std;
string s;

void send(const string &s) {
    cout << s << endl;
}

void check() {
    send("detect");
    cin >> s;
    while (s != "charge") {
        if (s == "wall") {
            send("left");
            send("move");
            check();
        } else if (s == "empty") {
            send("move");
            check();
        }
    }
    send("move");
}

int main() {
    check();
    send("!");
    return 0;
}