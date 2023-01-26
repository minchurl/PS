#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int mod = 998244353;
int n;
char s[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d", &n);
        scanf("%s", s);
        int res = 1;
        int p = 1;
        for (int i = 1; i < n; i++) {
            if (s[i - 1] != s[i]) {
                p = 1;
            }
            else {
                p = (p * 2) % mod;
            }
            res = (res + p) % mod;
        }
        printf("%d\n", res);
    }
    return 0;
}