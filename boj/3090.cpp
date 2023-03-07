#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int MAXN = 100005;
int n, t;
int arr[MAXN];
int original_arr[MAXN];
priority_queue<pii> pq;
void init() {
    while (pq.size()) {
        pq.pop();
    }
    for (int i = 0; i < n; i++) {
        arr[i] = original_arr[i];
        pq.push(pii(-arr[i], i));
    }
}
bool is_ok(int d) {
    init();
    LL sum = 0;
    while (pq.size()) {
        pii p = pq.top();
        pq.pop();
        if (-p.fi != arr[p.se]) {
            continue;
        }

        // left
        if (p.se != 0 && arr[p.se - 1] - arr[p.se] > d) {
            sum += arr[p.se - 1] - arr[p.se] - d;
            arr[p.se - 1] = arr[p.se] + d;
            pq.push(pii(-arr[p.se - 1], p.se - 1));
        }

        // right
        if (p.se != n - 1 && arr[p.se + 1] - arr[p.se] > d) {
            sum += arr[p.se + 1] - arr[p.se] - d;
            arr[p.se + 1] = arr[p.se] + d;
            pq.push(pii(-arr[p.se + 1], p.se + 1));
        }
    }
    return sum <= (LL)t;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &t);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &original_arr[i]);
        mx = max(mx, original_arr[i]);
    }
    int l = 0;
    int r = mx;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (is_ok(mid)) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    is_ok(l);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}