#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
const int MAXN = 1005;
int n, m;
int X[MAXN], Y[MAXN], Z[MAXN], W[MAXN];
vector<pii> delta;
int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &Z[i], &W[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            delta.pb(pii(X[i] + Z[j] - 1, 1));
            delta.pb(pii(X[i] + W[j], -1));
            delta.pb(pii(Y[i] + Z[j], -1));
            delta.pb(pii(Y[i] + W[j] + 1, 1));
        }
    }

    sort(all(delta));
    int k = 0;
    int sum = 0;
    int res = 0;
    int resVal = 0;
    int sz = delta.size();
    for (int i = 0; i < sz - 1; i++) {
        k += delta[i].se;
        sum += (delta[i + 1].fi - delta[i].fi) * k;
        if (sum > resVal) {
            resVal = sum;
            res = delta[i + 1].fi - 1;
        }
    }
    printf("%d\n", res);
    return 0;
}