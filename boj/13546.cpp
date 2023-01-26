#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXK = 100005;
const int MAXM = 100005;
const int SQRTMAXN = 317;
const int SQRTMAXK = 317;

struct Query {
    int s, e;
    int i;
};
Query query[MAXM];

int n, k;
int m;
int A[MAXN];
list<int> lst[MAXK];
int cnt[MAXK + SQRTMAXK];
int sqrtCnt[SQRTMAXK];

int ans[MAXM];

int getLength(int a) {
    if (lst[a].size() == 0) {
        return 0;
    }
    return lst[a].back() - lst[a].front();
}

void push(int i, bool isBack) {
    // back -> isBack true
    // front -> isBack false
    int a = A[i];
    int len = getLength(a);
    cnt[len]--;
    sqrtCnt[len / SQRTMAXK]--;

    if (isBack) {
        lst[a].push_back(i);
    }
    else {
        lst[a].push_front(i);
    }

    len = getLength(a);
    cnt[len]++;
    sqrtCnt[len / SQRTMAXK]++;
}

void pop(int i, bool isBack) {
    // back -> isBack true
    // front -> isBack false
    int a = A[i];
    int len = getLength(a);
    cnt[len]--;
    sqrtCnt[len / SQRTMAXK]--;

    if (isBack) {
        lst[a].pop_back();
    }
    else {
        lst[a].pop_front();
    }

    len = getLength(a);
    cnt[len]++;
    sqrtCnt[len / SQRTMAXK]++;
}


int main() {
    freopen("input.txt","r",stdin);
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &query[i].s, &query[i].e);
        query[i].i = i;
    }

    sort(query + 1, query + m + 1, [&](const Query x, const Query y) {
        if (x.s / SQRTMAXN == y.s / SQRTMAXN) {
            return x.e < y.e;
        }
        return x.s / SQRTMAXN < y.s / SQRTMAXN;
    });
    cnt[0] = m;
    sqrtCnt[0] = m;
    
    int s = 1;
    int e = 0;

    for (int i = 1; i <= m; i++) {
        Query q = query[i];
        while (e < q.e) {
            push(e + 1, true);
            e++;
        }
        while (s > q.s) {
            push(s - 1, false);
            s--;
        }
        while (s < q.s) {
            pop(s, false);
            s++;
        }
        while (e > q.e) {
            pop(e, true);
            e--;
        }
        int j;
        for (j = SQRTMAXK - 1; j >= 0; j--) {
            if (sqrtCnt[j] != 0) {
                break;
            }
        }
        j *= SQRTMAXK;
        j += SQRTMAXK - 1;
        while (!cnt[j]) {
            j--;
        }
        ans[q.i] = j;
    }

    for (int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
} 