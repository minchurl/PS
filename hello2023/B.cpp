#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 500005;
int n, k;
int A[MAXN];
int loc[MAXN];
set<int> S;
LL dst;
struct Node {
    int pre, next;
};
Node node[MAXN];
void initNode() {
    S.insert(0);
    S.insert(n + 1);
    dst = n + 1;

    loc[0] = 0;
    loc[n + 1] = n + 1;

    node[0].next = n + 1;
    node[n + 1].pre = 0;

}
void add(int pre, int curr, int next) {
    // disconnect pre - next
    dst -= abs(loc[pre] - loc[next]);

    // connect pre - curr
    node[pre].next = curr;
    node[curr].pre = pre;
    dst += abs(loc[pre] - loc[curr]);

    // connect curr - next
    node[curr].next = next;
    node[next].pre = curr;
    dst += abs(loc[curr] - loc[next]);
}
void add(int curr) {
    auto it = S.lower_bound(curr);
    int next = *it;
    it--;
    int pre = *it;
    add(pre, curr, next);
    S.insert(curr);
}

void del(int pre, int curr, int next) {
    // disconnect pre - curr
    dst -= abs(loc[pre] - loc[curr]);

    // disconnect curr - next
    dst -= abs(loc[curr] - loc[next]);

    // connect pre - next
    node[pre].next = node[curr].next;
    node[next].pre = node[curr].pre;
    dst += abs(loc[pre] - loc[next]);
}
void del(int curr) {
    int pre = node[curr].pre;
    int next = node[curr].next;
    del(pre, curr, next);
    S.erase(curr);
}
LL getDistance() {
    auto b = S.begin();
    auto e = S.end();
    b++;
    e--;
    e--;
    return dst - loc[*b] - (n + 1 - loc[*e]);
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    initNode();

    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
        loc[A[i]] = i;
    }
    for (int i = 1; i <= k; i++) {
        add(A[i]);
    }
    LL res = getDistance();

    for (int i = k + 1; i <= n; i++) {
        add(A[i]);
        del(A[i - k]);
        res = min(res, getDistance());
    }

    printf("%lld\n", res);
    return 0;
}