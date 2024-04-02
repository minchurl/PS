#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long LL;
const int MAXQ = 200005;
struct Query {
    int t;
    LL a, b, c;
    LL x;
}query[MAXQ];
vector<LL> X;
int n;
bool chk[MAXQ];
int t[MAXQ];
void update(int i) {
    for (; i <= n; i += (i & (-i))) {
        t[i]++;
    }
}

int get(int i) {
    int sum = 0;
    for (; i > 0; i -= (i & (-i))) {
        sum += t[i];
    }
    return sum;
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            LL a, b;
            scanf("%lld %lld", &a, &b);
            query[i].t = 1;
            query[i].a = a;
            query[i].b = b;
            if (a == 0) {
                X.pb(0);
            }
            else {
                LL x = (-b) / a;
                LL remain = (-b) % a;
                query[i].x = 2 * x + (remain == 0 ? 0 : (remain > 0 ? 1 : -1));
                X.pb(query[i].x);
            }
        }
        else {
            LL c;
            scanf("%lld", &c);
            query[i].t = 2;
            query[i].c = c;
            query[i].x = 2 * c;
            X.pb(2 * c);
        }
    }
    sort(all(X)); X.erase(unique(all(X)), X.end());

    for (int i = 0; i < n; i++) {
        query[i].x = lower_bound(all(X), query[i].x) - X.begin() + 1;
    }
    int base = 1;
    bool contain_zero = false;
    for (int i = 0; i < n; i++) {
        Query q = query[i];
        if (q.t == 1) {
            if (q.a == 0) {
                if (q.b == 0) {
                    contain_zero = true;
                }
                else {
                    base *= q.b > 0 ? 1 : -1;
                }
            }
            else {
                update(q.x);
                if (q.a > 0) {
                    base *= -1;
                }
                chk[q.x] = true;
            }
        }
        else {
            if (contain_zero || chk[q.x]) {
                printf("0\n");
            }
            else if ((get(q.x) % 2 ? -1 : 1) * base > 0) {
                printf("+\n");
            }
            else {
                printf("-\n");
            }
        }
    }
    return 0;
}