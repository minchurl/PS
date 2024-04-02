#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 1005;
struct Recode {
    int type;
    int a, b;
    char x, y;
    Recode(){}
    Recode(int _type, int _a, int _b) {
        type = _type, a = _a, b = _b;
    }

    Recode(int _type, int _a, char _x, char _y) {
        type = _type, a = _a, x = _x, y = _y;
    }
};
vector<Recode> recode[2];

char s[10 * MAXN];

char remain_one_color(char a, char b) {
    return 'R' + 'G' + 'B' - a - b;
}

char remain_two_color(char a, char &b, char &c) {
    if (a == 'R') {
        b = 'G';
        c = 'B';
    }
    else if (a == 'G') {
        b = 'B';
        c = 'R';
    }
    else {
        b = 'R';
        c = 'B';
    }
}

void operation1(int a, int b) {
    char c = remain_one_color(s[a], s[b]);
    if (a == n && b == 1) {
        recode[idx].pb((idx == 0) ? Recode(1, a, b) : Recode(2, 0, s[a], s[b]));
        s[1] = c;
        n--;
    }
    else {
        recode[idx].pb((idx == 0) ? Recode(1, a, b) : Recode(2, a, s[a], s[b]));
        s[a] = c;
        for (int i = a + 1; i < n; i++) {
            s[i] = s[i + 1];
        }
        n--;
    }
}
void operation2(int a, char x, char y) {
    // don't use a = n + 1 case.
    if (a >= 1 && a <= n) {
        recode[idx].pb((idx == 0) ? Recode(2, a, x, y) : Recode(1, a, a + 1));
        for (int i = n + 1; i >= a + 2; i--) {
            a[i] = a[i - 1];
        }
        s[a] = x;
        s[a + 1] = y;
        n++;
    }
    else if (a == 0) {
        recode[idx].pb((idx == 0) ? Recode(2, a, x, y) : Recode(1, n + 1, 1));
        s[n + 1] = x;
        s[1] = y;
        n++;
    }
}

void calc() {
    while (true) {
        
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    return 0;
}