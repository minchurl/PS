#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;

const int MAXN = 1000005;
const int SQRTN = 1000;
int n;
int arr[MAXN];
int qn;
vector<int> lst;

struct Query {
    int l, r;
    int idx;
    int res;
}query[MAXN];

int res;
int cnt[MAXN];
void add(int x) {
    if (cnt[x] == 0) {
        res++;
    }
    cnt[x]++;
}
void del(int x) {
    cnt[x]--;
    if (cnt[x] == 0) {
        res--;
    }
}

int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){ 
        scanf("%d", &arr[i]);
        lst.pb(arr[i]);
    }
    sort(all(lst)); lst.erase(unique(all(lst)), lst.end());

    for (int i = 1; i <= n; i++) {
        arr[i] = lower_bound(all(lst), arr[i]) - lst.begin() + 1;
    }

    scanf("%d", &qn);

    for (int i = 0; i < qn; i++) {
        scanf("%d %d", &query[i].l, &query[i].r);
        query[i].idx = i;
        query[i].res = 0;
    }
    sort(query, query + qn, [&](const Query x, const Query y) {
        if (x.l / SQRTN == y.l / SQRTN) {
            return x.r < y.r;
        }
        return x.l < y.l;
    });

    res = 0;
    int l = 0;
    int r = 0;
    cnt[0] = 1;
    res = 1;

    for (int i = 0; i < qn; i++) {
        // expand
        while(l > query[i].l) {
            add(arr[l - 1]);
            l--;
        }
        while (r < query[i].r) {
            add(arr[r + 1]);
            r++;
        }

        // reduce
        while (l < query[i].l) {
            del(arr[l]);
            l++;
        }
        while (r > query[i].r) {
            del(arr[r]);
            r--;
        }
        query[i].res = res;
    }

    sort(query, query + qn, [&](const Query x, const Query y) {
        return x.idx < y.idx;
    });

    for (int i = 0; i < qn; i++) {
        printf("%d\n", query[i].res);
    }
    return 0;
}