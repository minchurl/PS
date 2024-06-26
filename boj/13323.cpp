#include<bits/stdc++.h>
using namespace std;
priority_queue<int> pq;
int n;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    long long res = 0;
    int x;
    scanf("%d", &x);
    pq.push(x);
    pq.push(x);
    for (int i = 1; i < n; i++) {
        scanf("%d", &x);
        x = x - i;
        pq.pop();
        if (x < pq.top()) {
            res += pq.top() - x;
        }
        pq.push(x);
        pq.push(x);
    }
    printf("%lld\n", res);
    return 0;
}