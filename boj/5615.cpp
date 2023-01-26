#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;


ULL modPow(ULL a, ULL p, ULL m) {
    // a ^ p
    if (p <= 0) {
        return 1;
    }
    if (p == 1) {
        return a;
    }
    ULL res = modPow(a, p / 2, m);
    res = (res * res) % m;
    if (p % 2) {
        res = (res * a) % m;
    }

    return res;
}


int A[15] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37, 41, 43, 47, 53};


bool millerRabinTest(ULL a, ULL d, ULL r, ULL n) {
    if (a >= n) {
        return true;
    }

    ULL aD = modPow(a, d, n);
    if (aD == 1 || aD == n - 1) {
        return true;
    }

    ULL x = aD;
    for (int i = 1; i < r; i++) {
        x = (x * x) % n;
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}

bool isPrime(ULL n) {
    // using Miller-Rabin primarlity test

    if (n == 2) {
        return true;
    }

    if (n % 2 == 0) {
        return false;
    }

    if (n == 3) {
        return true;
    }

    ULL d = n - 1;
    ULL r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    for (int i = 0; i < 15; i++) {
        ULL a = A[i];
        if (!millerRabinTest(a, d, r, n)) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen("input.txt","r",stdin);
    int n;
    scanf("%d", &n);

    int res = 0;
    while (n--) {
        ULL x;
        scanf("%llu", &x);
        x = x * 2 + 1;
        res += isPrime(x);
    }

    printf("%d\n", res);

    return 0;
}