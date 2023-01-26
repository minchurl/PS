#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const int MAXN = 10;
int n;
int d[MAXN];
vector<int> lst;
void constructD(int x) {
    n = 0;
    while (x) {
        d[n++] = x % 10;
        x /= 10;
    }
    for (int i = 0; i < n / 2; i++) {
        swap(d[i], d[n - i - 1]);
    }
}
void constructList() {
    lst.clear();
    for (int code = 0; code < (1 << (n - 1)); code++) {
        int c = code;
        int sum = 0;
        int val = 0;
        for (int i = 0; i < n; i++) {
            val = val * 10 + d[i];
            if (c % 2) {
                sum += val;
                val = 0;
            }
            c /= 2;
        }
        sum += val;
        lst.pb(sum);
    }
    sort(all(lst));lst.erase(unique(all(lst)), lst.end());
}
int Power(int x, int y) { // x ^ y
    LL res = 1;
    while (y--) {
        res *= x;
        if (res > (LL)(1e9)) {
            return -1;
        }
    }
    return res;
}
int DM(int m) {
    LL res = 0;
    for (int i = 0; i < n; i++) {
        LL val = Power(d[i], m);
        if (val == -1) {
            return -1;
        }
        res += val;
    }
    if (res > (LL) (1e9)) {
        return -1;
    }

    return (int)res;
}
bool isInList(int x) {
    int idx = lower_bound(all(lst), x) - lst.begin();
    if (idx >= lst.size() || lst[idx] != x) {
        return false;
    }
    return true;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        int x;
        scanf("%d", &x);
        constructD(x);
        constructList();
        int res = 0;
        if (DM(1) == DM(2)) {
            printf("Hello, BOJ 2023!\n");
            continue;
        }
        for (int i = 1; i <= 30; i++) {
            int x = DM(i);
            if (x == -1) {
                break;
            }
            res += isInList(x);
        }
        printf("%d\n", res);
    }
    return 0;
}