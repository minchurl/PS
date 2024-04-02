#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int inf = 0x3fffffff;
int n;
int arr[MAXN];
bool is_possible(int len) {
    int mono = 0;
    int need_mono = 1;

    for (int i = 1; i <= n; i++) {
        mono += arr[i] <= len ? 1 : 0;
        if (arr[i] > 2 * len) {
            need_mono += (arr[i] - 1) / len - 1;
        }
    }

    return mono >= need_mono;
}
int main() {
    freopen("input.txt" ,"r", stdin);
    scanf("%d", &n);
    int l = inf;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        l = min(l, arr[i]);
        r = max(r, arr[i]);
    }

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