#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
const LL MAXT = (1 << 20) + 5;
const LL inf = (1LL << 60) + 5;
LL n, x, y, t;
LL p;
LL p2;
LL dst[MAXT];
priority_queue<pll> pq;
void dijkstra(LL st, LL base) {
    for (int i = 0; i <= p2; i++) {
        dst[i] = inf;
    }
    dst[st] = 0LL;
    pq.push(pll(0, st));
    while (pq.size()) {
        pll p = pq.top();
        pq.pop();
        if (dst[p.se] != -p.fi) {
            continue;
        }
        LL nxt;
        // ^t
        nxt = (p.se) ^ t;
        if (nxt + base < n && nxt <= p2 && dst[nxt] > dst[p.se] + 1) {
            dst[nxt] = dst[p.se] + 1;
            pq.push(pll(-dst[nxt], nxt));
        }
        // ^t + 1
        nxt = (p.se) ^ t + 1;
        if (nxt + base < n && nxt <= p2 && dst[nxt] > dst[p.se] + 1) {
            dst[nxt] = dst[p.se] + 1;
            pq.push(pll(-dst[nxt], nxt));
        }
    }
}
int main() {
    scanf("%lld %lld %lld %lld", &n, &x, &y, &t);

    for (p = 0; (1LL << p) <= t; p++) {
    }

    p2 = (1LL << p);
    if (x / p2 > y / p2) {
        printf("-1\n");
        return 0;
    }

    if (x / p2 == y / p2) {
        dijkstra(x % p2, 0);
        printf("%lld\n", (dst[y % p2] == inf) ? (-1) : dst[y % p2]);
        return 0;
    }

    LL res = 0;
    if (dst[p2] == inf) {
        printf("-1\n");
        return 0;
    }
    res = dst[p2];
    LL cur = x / p2 + 1;
    // x / p2 -> x / p2 + 1

    // aim : y / p2
    dijkstra(0, 0);
    if (dst[p2] == inf) {
        printf("-1\n");
        return 0;
    }
    res += dst[p2] * (y / p2 - cur);
    cur = y / p2;

    dijkstra(0, y / p2 * p2);
    if (dst[y % p2] == inf) {
        printf("-1\n");
        return 0;
    }
    res += dst[y % p2];

    printf("%lld\n", res);

    return 0;
}