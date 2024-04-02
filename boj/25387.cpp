#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
#define mod(x) (((x) % M + M) % M)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 300005;
const int MAXQ = 300005;
const LL M = 998244353;
struct Linked_list {
    LL n, q;
    LL val;
    LL C[MAXQ];
    set<LL> alived;
    void init(LL _n, LL _q) {
        n = _n;
        q = _q;
        alived.insert(0);
        alived.insert(q + 1);
        C[0] = C[q + 1] = 0;
    }
    void insert(LL i, LL c) {
        auto it = alived.lower_bound(i);
        LL r = *it;
        it--;
        LL l = *it;
        C[i] = c;

        val = mod(val - mod(mod(l * (r - i)) * C[l]) + mod(mod((r - i) * i) * C[i]));
        alived.insert(i);
    }

    void del(LL i) {
        auto it = alived.lower_bound(i);
        it++;
        LL r = *it;
        it--;
        it--;
        LL l = *it;

        val = mod(val + mod(mod(l * (r - i)) * C[l]) - mod(mod((r - i) * i) * C[i]));
        alived.erase(i);
    }

    LL get(LL i) {
        return mod(mod(val * i) * (n + 1 - i));
    }
}lst;
struct Query {
    LL i, idx, c;
    bool is_start;
    Query(){}
    Query (LL _i, LL _idx, LL _c, bool _is_start) {
        i = _i;
        idx = _idx;
        c = _c;
        is_start = _is_start;
    }
};
vector<Query> queries;
LL n, q;
LL A[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%lld %lld", &n, &q);
    for (int i = 1; i <= q; i++) {
        LL l, r, c;
        scanf("%lld %lld %lld", &l, &r, &c);
        queries.pb(Query(l, i, c, true));
        queries.pb(Query(r, i, c, false));
    }
    sort(all(queries), [&](const Query x, const Query y) {
        if (x.i == y.i) {
            return x.is_start > y.is_start;
        }
        return x.i < y.i;
    });

    lst.init(n, q);

    LL idx = 0;
    LL sz = queries.size();
    LL res = 0;
    for (LL i = 1; i <= n; i++) {
        LL x;
        while (idx < sz && queries[idx].i <= i && !(queries[idx].i == i && !queries[idx].is_start)) {
            if (queries[idx].is_start) {
                lst.insert(queries[idx].idx, queries[idx].c);
            }
            else {
                lst.del(queries[idx].idx);
            }
            idx++;
        }

        res = mod(res + lst.get(i));


        while (idx < sz && queries[idx].i <= i) {
            if (queries[idx].is_start) {
                lst.insert(queries[idx].idx, queries[idx].c);
            }
            else {
                lst.del(queries[idx].idx);
            }
            idx++;
        }
    }

    printf("%lld\n", res);
    return 0;
}