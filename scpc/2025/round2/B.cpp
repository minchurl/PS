#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef pair<int, int> pii;
typedef long long LL;
const int MAXN = 100005;
const int MAXM = 200005;

struct BoardDiff {
    int i, j;
    int diff;
    BoardDiff() {

    }
    BoardDiff(int _i, int _j, int _diff) {
        i = _i;
        j = _j;
        diff = _diff;
    }
};
vector<BoardDiff> boardDiffs;

struct Paint {
    int i;
    pii p;
    Paint() {

    }
    Paint(int _i, pii _p) {
        i = _i;
        p = _p;
    }
};
vector<Paint> paints;
int N, M;
int cnt[MAXN], sum[4 * MAXN];
void init() {
    boardDiffs.clear();
    paints.clear();
    for (int i = 0; i < MAXN; i++) {
        cnt[i] = 0;
    }
    for (int i = 0; i < 4 * MAXN; i++) {
        sum[i] = 0;
    }
}

void update(int u, int l, int r, int p, int d) {
    if (p < l || p > r) {
        return;
    }
    if (l == r) {
        if (cnt[p] == 1 && d == -1) {
            sum[u] = 0;
        }
        else if (cnt[p] == 0 && d == 1) {
            sum[u] = 1;
        }
        cnt[p] += d;
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) {
        update(2 * u, l, mid, p, d);
    }
    else if (p > mid) {
        update(2 * u + 1, mid + 1, r, p, d);
    }

    sum[u] = sum[2 * u] + sum[2 * u + 1];
}

void update(int i, int d) {
    update(1, 1, N, i, d);
}

int get(int u, int l, int r, int s, int e) {
    if (e < l || s > r || s > e) {
        return 0;
    }
    if (s <= l && r <= e) {
        return sum[u];
    }
    int mid = (l + r) >> 1;
    if (e <= mid) {
        return get(2 * u, l, mid, s, e);
    }
    else if (s > mid) {
        return get(2 * u + 1, mid + 1, r, s, e);
    }

    return get(2 * u, l, mid, s, mid) + get(2 * u + 1, mid + 1, r, mid + 1, e);
}
int get(int l, int r) {
    return get(1, 1, N, l, r);
}

void solve() {
    for (int j = 1; j <= N; j++) {
        int si, ei;
        scanf("%d %d", &si, &ei);
        boardDiffs.pb(BoardDiff(si, j, 1));
        boardDiffs.pb(BoardDiff(ei + 1, j, -1));
    }

    for (int idx = 1; idx <= M; idx++) {
        int i;
        int sj, ej;
        scanf("%d %d %d", &i, &sj, &ej);
        paints.pb(Paint(i, pii(sj, ej)));
    }

    sort(all(boardDiffs), [&](const BoardDiff p, const BoardDiff q) {
        return p.i < q.i;
    });

    sort(all(paints), [&](const Paint p, const Paint q) {
        if (p.i == q.i) {
            return p.p.fi < q.p.fi;
        }
        return p.i < q.i;
    });

    int bn = boardDiffs.size();
    int bi = 0;

    int pn = paints.size();

    LL res1 = 0;
    int res2 = 0;

    vector<pii> lst; 
    for (int pi = 0; pi < pn; pi++) {
        while (bi < bn && paints[pi].i >= boardDiffs[bi].i) {
            update(boardDiffs[bi].j, boardDiffs[bi].diff);
            bi++;
        }
        pii curr = paints[pi].p;
        lst.clear();
        while (pi + 1 < pn && paints[pi].i == paints[pi + 1].i) {
            pi++;
            if (curr.se + 1 >= paints[pi].p.fi) {
                curr.se = max(curr.se, paints[pi].p.se);
            }
            else {
                int val = get(curr.fi, curr.se);
                if (val != 0) {
                    lst.pb(curr);
                    res1 += val;
                }
                curr = paints[pi].p;
            }
        }
        int val = get(curr.fi, curr.se);
        if (val != 0) {
            lst.pb(curr);
            res1 += val;
        }
        int ln = lst.size();
        if (ln == 0) {
            continue;
        }
        res2++;
        for (int k = 0; k < ln - 1; k++) {
            if (get(lst[k].se + 1, lst[k + 1].fi - 1) > 0) {
                res2++;
            }
        }
    }

    printf("%lld %d\n", res1, res2);
}
int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &N, &M);

        init();
        solve();
    }
    return 0;

}