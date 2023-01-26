#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 100005;
const int MAXA = 500005;
int n;
int m[2];
int cnt[2][MAXA];
vector<int> lst[2];
void init(int state) {
    for (int x: lst[state]) {
        cnt[state][x] = 0;
    }
    lst[state].clear();
    m[state] = 0;
}
void add(int state, int x, int v) {
    if (v == 0) {
        return;
    }
    if (!cnt[state][x]) {
        lst[state].pb(x);
    }
    cnt[state][x] += v;
    m[state] += v;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    int curr = 0;
    int pre = 1;
    while (TC--) {
        scanf("%d", &n);
        init(pre);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            add(pre, x, 1);
        }

        while (m[pre] != 1) {
            sort(all(lst[pre]));
            int sz = lst[pre].size();

            for (int i = 0; i < sz; i++) {
                add(curr, 0, cnt[pre][lst[pre][i]] - 1);
            }
            for (int i = 1; i < sz; i++) {
                add(curr, lst[pre][i] - lst[pre][i - 1], 1);
            }
            init(pre);
            curr = 1 - curr;
            pre = 1 - pre;
        }
        printf("%d\n", lst[pre].front());
    }
    return 0;
}