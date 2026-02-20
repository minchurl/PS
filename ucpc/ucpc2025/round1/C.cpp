#include<bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define eb emplace_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 250005;
const int MAXQ = 250005;
const int MAXX = 1000005;
LL nt[MAXX];
LL sumt[MAXX];
void init_t() {
    for (int i = 0; i < MAXX; i++) {
        nt[i] = 0LL;
        sumt[i] = 0LL;
    }
}
void update_nt(int i, LL v) {
    for (; i < MAXX; i += (i & -i)) {
        nt[i] += v;
    }
}
void update_reverse_nt(int i, LL v) {
    update_nt(MAXX - i - 1, v);
}
LL get_nt(int i) {
    LL res = 0;
    for (; i > 0; i -= (i & -i)) {
        res += nt[i];
    }
    return res;
}
LL get_reverse_nt(int i) {
    return get_nt(MAXX - i - 1);
}

void update_sumt(int i, LL v) {
    for (; i < MAXX; i += (i & -i)) {
        sumt[i] += v;
    }
}
void update_reverse_sumt(int i, LL v) {
    update_sumt(MAXX - i - 1, v);
}
LL get_sumt(int i) {
    LL res = 0;
    for (; i > 0; i -= (i & -i)) {
        res += sumt[i];
    }
    return res;
}
LL get_reverse_sumt(int i) {
    return get_sumt(MAXX - i - 1);
}

struct Event {
    int sum;
    bool is_raser;
    int idx;
    Event() {}
    Event(int _sum, bool _is_raser, int _idx) {
        sum = _sum;
        is_raser = _is_raser;
        idx = _idx;
    }
};
vector<Event> events;
int n, q;
vector<pii> rasers, stores;
LL minimum_cost[MAXQ];
int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        events.eb(l + r, false, i);
        stores.eb(l, r);
    }

    for (int i = 0; i < q; i++) {
        int s, e;
        scanf("%d %d", &s, &e);
        events.eb(s + e, true, i);
        rasers.eb(s, e);
    }

    sort(all(events), [&](const Event x, const Event y) {
        if (x.sum == y.sum) {
            if (x.is_raser == y.is_raser) {
                return x.idx < y.idx;
            }
            return x.is_raser < y.is_raser;
        }
        return x.sum < y.sum;
    });

    // find l + r <= s + e and s < r
    // use reverse fenwick tree
    init_t();
    for (Event event: events) {
        if (event.is_raser) {
            int s = rasers[event.idx].first;
            int e = rasers[event.idx].second;
            LL num = get_reverse_nt(s + 1);
            LL sum = get_reverse_sumt(s + 1);
            minimum_cost[event.idx] += sum - (LL)s * num;
        }
        else {
            int l = stores[event.idx].first;
            int r = stores[event.idx].second;
            update_reverse_nt(r, r - l);
            update_reverse_sumt(r, (LL)r * (r - l));
        }
    }


    // find l + r > s + e and e > l
    // use normal fenwick tree
    reverse(all(events));
    init_t();
    for (Event event: events) {
        if (event.is_raser) {
            int s = rasers[event.idx].first;
            int e = rasers[event.idx].second;
            LL num = get_nt(e - 1);
            LL sum = get_sumt(e - 1);
            minimum_cost[event.idx] += (LL)e * num - sum;
        }
        else {
            int l = stores[event.idx].first;
            int r = stores[event.idx].second;
            update_nt(l, r - l);
            update_sumt(l, (LL)l * (r - l));
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%lld\n", 2 * minimum_cost[i]);
    }
    return 0;
}