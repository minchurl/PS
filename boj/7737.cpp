#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 100005;
const int MAXPRIMENUMBER = 20005;
int prime[MAXPRIMENUMBER];
vector<LL> primePower[MAXPRIMENUMBER];
int n;
LL m;
int pn;
bool chk[2 * MAXN];
LL tree[65538];
int cnt[MAXPRIMENUMBER];
vector<pii> memo[2 * MAXN];

void init() {
    for (int i = 1; i <= 65536; i++) {
        tree[i] = 1;
    }
}

void gatherPrimeNumber() {
    primePower[pn].pb(1);
    primePower[pn].pb(2);
    prime[pn++] = 2;
    for (int i = 3; i <= 2 * n; i += 2) {
        if (chk[i]) {
            continue;
        }
        primePower[pn].pb(1);
        primePower[pn].pb(i);
        prime[pn++] = i;
        for (int j = i * 2; j <= 2 * n; j += i) {
            chk[j] = true;
        }
    }
}

void update(int x, int l, int r, int p, LL v) {
    if (l == r) {
        tree[x] = v;
        return;
    }

    int mid = (l + r) >> 1;
    if (p <= mid) {
        update(2 * x, l, mid, p, v);
    }
    else {
        update(2 * x + 1, mid + 1, r, p, v);
    }
    tree[x] = (tree[2 * x] * tree[2 * x + 1]) % m;
}

void update(int p, LL v) {
    update(1, 0, pn - 1, p, v);
}

LL get() {
    return tree[1];
}

LL getPrimePower(int i, int x) {
    // prime[i]^x
    while (primePower[i].size() <= x) {
        primePower[i].pb((primePower[i][1] * primePower[i].back()) % m);
    }
    return primePower[i][x];
}

void generateMemo() {
    for (int i = 1; i <= 2 * n - 4; i++) {
        int x = i;
        if (i > n + 1 && i % 2 == 0) {
            continue;
        }
        for (int j = 0; j < pn && prime[j] <= x; j++) {
            if (x % prime[j]) {
                continue;
            }
            int c = 0;
            while (x % prime[j] == 0) {
                x /= prime[j];
                c++;
            }
            memo[i].pb(pii(j, c));
        }
    }
}

void adjust(int x, int d) {
    for (pii p: memo[x]) {
        cnt[p.fi] += d * p.se;
        update(p.fi, getPrimePower(p.fi, cnt[p.fi]));
    }
}

LL res = 0;
void calc() {
    generateMemo();

    for (int i = 1; i <= n - 2; i++) {
        adjust(2 * i - 1, 1);

        cnt[0]++;
        update(0, getPrimePower(0, cnt[0]));

        adjust(i + 1, -1);
        
        res = (res + get()) % m;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %lld", &n, &m);

    init();
    gatherPrimeNumber();
    calc();

    printf("%lld\n", res);
    return 0;
}