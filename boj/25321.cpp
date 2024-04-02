#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 300005;
const LL M = 1000000007;
int n;
int cnt[MAXN];
LL fac[MAXN];
LL inv[MAXN];
LL C[MAXN];
LL inv_fac[MAXN];
LL res[MAXN];
char s[MAXN];
stack<int> st;
void calc() {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (-(M / i) * inv[M % i]) % M;
    }

    inv_fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        inv_fac[i] = (inv_fac[i - 1] * inv[i]) % M;
    }

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = (fac[i - 1] * i) % M;
    }
    C[0] = 1;
    for (int i = 1; i <= n / 2; i++) {
        C[i] = (((fac[2 * i] * inv_fac[i]) % M) * inv_fac[i]) % M;
        C[i] = (C[i] * inv[i + 1]) % M;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", s);
    n = strlen(s);
    calc();
    int x = 0;
    st.push(0);
    res[0] = 1;
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            if (s[i] == '?') {
                cnt[st.top()]++;
                res[i] = 1;
                st.push(i);
            }
            else if (s[i] == ':') {
                int l = st.top();
                res[l] = (res[l] * C[cnt[l]]) % M;
                st.pop();
                res[st.top()] = (res[st.top()] * res[l]) % M;
            }
            else {
                return !printf("0\n");
            }
        }
        else {
            if (s[i] < 'a' || s[i] > 'z') {
                return !printf("0\n");
            }
        }
    }
    res[0] = (res[0] * C[cnt[0]]) % M;
    res[0] = (res[0] + M) % M;
    printf("%lld\n", res[0]);
    return 0;
}