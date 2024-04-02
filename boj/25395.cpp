#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 1000005;
int X[MAXN];
int H[MAXN];
queue<int> Q;
int main() {
    freopen("input.txt", "r", stdin);
    int n, s;
    int l, r;
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &X[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }
    int e = s;
    l = r = X[s];
    Q.push(s);
    int res = 1;
    while (Q.size()) {
        int i = Q.front();
        Q.pop();
        l = min(l, X[i] - H[i]);
        r = max(r, X[i] + H[i]);
        while (s > 1 && X[s - 1] >= l) {
            s--;
            Q.push(s);
            res++;
        }
        while (e < n && X[e + 1] <= r) {
            e++;
            Q.push(e);
            res++;
        }
    }

    for (int i = s; i <= e; i++) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}