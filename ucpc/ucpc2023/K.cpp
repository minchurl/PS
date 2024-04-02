#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 200005;
int n, t;
int a[MAXN];
priority_queue<int> pq;
void init() {
    while(pq.size()) {
        pq.pop();
    }
}
bool is_possible(int rn) {
    int st = max(1, a[0] - t + 1);
    int ed = st + t - 1;
    init();
    pq.push(-ed);

    for (int i = 1; i < n; i++) {
        int l_st = max(1, a[i] - t + 1);
        int r_st = a[i];
        int st, ed;

        while (pq.size() && -pq.top() < l_st) {
            pq.pop();
        }
        if (pq.size() < rn) {
            st = l_st;
            ed = st + t - 1;
            pq.push(-ed);
            continue;
        }

        if (-pq.top() >= r_st) {
            return false;
        }
        st = -pq.top() + 1;
        ed = st + t - 1;
        pq.pop();
        pq.push(-ed);
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int l = 1;
    int r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (is_possible(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }

    printf("%d\n", l);
    return 0;
}