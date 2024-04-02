#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 300005;
const int MAXM = 300005;
int m, n;
int chk[MAXN];
pii arr[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &m, &n);
    if (n == m) {
        return !printf("-1\n");
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i].fi);
        arr[i].fi--;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i].se);
        arr[i].se--;
    }
    sort(arr + 1, arr + n + 1);

    for (int i = 1; i <= n; i++) {
        if (chk[arr[i].se]) {
            return !printf("-1\n");
        }
        chk[arr[i].se] = i;
    }

    int curr = 1;

    for (int i = (arr[1].se + 1) % m; i != arr[1].se; i = (i + 1) % m) {
        if (chk[i] == 0) {
            continue;
        }
        if (chk[i] == curr + 1) {
            curr++;
        }
        else {
            return !printf("-1\n");
        }
    }
    for (int i = 1; i <= n; i++) {
        swap(arr[i].fi, arr[i].se);
    }

    sort(arr + 1, arr + n + 1);
    LL res = 0;
    int ed = -1;
    for (int i = 1; i <= n; i++) {
        int x = arr[i].se;
        if (x < arr[i].fi || x <= ed) {
            x += m;
        }

        res += (LL) (x - arr[i].fi);
        ed = x;
    }

    printf("%lld\n", res);
    return 0;
}