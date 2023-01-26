#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const unsigned int INF = 0x8000000;
vector<bool> chk;
vector<unsigned int> lst;
int main() {
    freopen("input.txt","r",stdin);
    chk.resize(INF);
    lst.pb(2);
    for (unsigned int i = 3; i < INF; i += 2) {
        if (chk[i]) {
            continue;
        }
        lst.pb(i);
        for (unsigned int j = i * 2; j < INF; j += i) {
            chk[j] = true;
        }
    }
    long long n;
    scanf("%lld", &n);
    for (unsigned int x : lst) {
        while (n % x == 0) {
            printf("%d\n", x);
            n /= x;
        }
    }
    if (n != 1) {
        printf("%d\n", n);
    }
    return 0;
}