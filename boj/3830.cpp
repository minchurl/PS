#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int MAXN = 100005;

typedef pair<int, int> pii;

int n, m;
int par[MAXN], dst[MAXN];

pii find_par(int x) {
    if (par[x] == x) {
        return pii(x, 0);
    }
    pii res = find_par(par[x]);
    par[x] = res.first;
    dst[x] = res.second + dst[x];

    return pii(par[x], dst[x]);
}

void init() {
    for (int i = 1; i <= n; i++) {
        par[i] = i;
        dst[i] = 0;
    }
}

void merge(int a, int b, int d) {
    pii parA = find_par(a);
    pii parB = find_par(b);

    if (parA.fi == parB.fi) {
        return ;
    }

    par[parA.fi] = parB.fi;
    dst[parA.fi] = parB.se - parA.se + d;
    
}

void get(int a, int b) {
    pii parA = find_par(a);
    pii parB = find_par(b);

    if (parA.fi != parB.fi) {
        printf("UNKNOWN\n");
    }
    else {
        printf("%d\n", parA.se - parB.se);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    char inputString[3];
    while (true) {
        scanf("%d %d", &n, &m);
        if (n == 0 && m == 0) {
            break;
        }

        init();

        for (int i = 1; i <= m; i++) {
            scanf("%s", inputString);

            if (inputString[0] == '!') {
                int a, b, d;
                scanf("%d %d %d", &a, &b, &d);
                merge(a, b, d);
            }
            else {
                int a, b;
                scanf("%d %d", &a, &b);
                get(a, b);
            }
        }
    }
    return 0;
}