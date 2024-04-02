#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 300005;
const int MAXM = 1000005;
int n;
int L[MAXM], R[MAXM];
vector<pii> range;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < MAXM; i++) {
        L[i] = MAXM;
        R[i] = -1;
    }
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        range.pb(pii(l, r));
        L[r] = min(L[r], l);
        R[l] = max(R[l], r);
    }
    sort(all(range)); range.erase(unique(all(range)), range.end());
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        if (*(lower_bound(all(range), pii(l, r))) == pii(l, r)) {
            printf("1\n");
            continue;
        }
        if (L[r] <= l && R[l] >= r) {
            printf("2\n");
        }
        else {
            printf("-1\n");
        }
    }

    return 0;
}