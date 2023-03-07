#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
priority_queue<int> pq;
int n;
long long res[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    int x;
    scanf("%d", &x);
    res[0] = x;
    pq.push(x);
    pq.push(x);
    for (int i = 1; i < n; i++) {
        scanf("%d", &x);
        x = x - i;
        pq.pop();
        res[i] = x;
        if (x < pq.top()) {
            res[i] = pq.top();
        }
        pq.push(x);
        pq.push(x);
    }
    long long y = res[n - 1];
    for (int i = n - 2; i >= 0; i--){ 
        res[i] = min(res[i], y);
        y = res[i];
    }
    for (int i = 0; i < n; i++) {
        printf("%lld\n", res[i] + i);
    }
    return 0;
}