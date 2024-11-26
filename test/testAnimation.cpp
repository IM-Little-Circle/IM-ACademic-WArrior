#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "TEXT ADVENTURE";
    for(int i=0; i<s.length(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    return 0;
}