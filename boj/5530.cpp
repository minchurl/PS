#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int n;
char tower[MAXN];
bool isUsed[MAXN];
queue<int> qI, qJ;
stack<int> stO;
void init() {
    for (int i = 0; i < n; i++) {
        isUsed[i] = false;
    }
    while (qI.size()) {
        qI.pop();
    }
    while (qJ.size()) {
        qJ.pop();
    }
    while (stO.size()) {
        stO.pop();
    }
}
bool isPossible(int oN) {
    init();
    for (int i = n - 1; i >= 0; i--) {
        if (tower[i] == 'I') {
            qI.push(i);
        }
        else if (tower[i] == 'O' && stO.size() < oN && qI.size() > 0) {
            isUsed[qI.front()] = true;
            stO.push(i);
            qI.pop();
        }
    }

    if (stO.size() < oN) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (tower[i] == 'O' || isUsed[i] || stO.size() == 0) {
            continue;
        }
        if (i > stO.top()) {
            return false;
        }
        isUsed[i] = true;
        stO.pop();
    }
    return stO.size() == 0;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    scanf("%s", tower);
    int l = 0;
    int r = n / 3;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (isPossible(mid)) {
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }
    printf("%d\n", l);
    return 0;
}