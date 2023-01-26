#include<bits/stdc++.h>

#define fi first
#define se second

#define pb push_back
#define all(v) (v).begin(), (v).end()

using namespace std;
typedef pair<int, int> pii;

const int MAXN = 505;
const int MAXM = 500;
const int MAXQ = 100000;
const int MAXH = 1000000;

struct Query {
    pii x, y;
}Q[MAXQ + 5];

struct Jobs {
    int type;           // 0 -> point / 1 -> query
    int val;
    pii cor;            // if point -> point coordinate
    int queryIdx;    // else -> query index

    Jobs() {}

    // type -> 0
    Jobs(int _val, pii _cor) {
        type = 0;
        val = _val;
        cor = _cor;
        queryIdx = 0;
    }

    // type -> 1
    Jobs(int _val, int _queryIdx) {
        type = 1;
        val = _val;
        cor = pii(0, 0);
        queryIdx = _queryIdx;
    }

};

vector<Jobs> jobs;

pii dxy[4] = {pii(-1, 0), pii(1, 0), pii(0, -1), pii(0, 1)};
int n, m, q;
int V[MAXN + 5][MAXM + 5];
int resHeight[MAXQ + 5];
bool isConnected[MAXQ];
int L[MAXQ + 5], R[MAXQ + 5], M[MAXQ + 5];
pii par[MAXN + 5][MAXM + 5];

pii findPar(pii x) {
    return (par[x.fi][x.se] == x) ? (x) : (par[x.fi][x.se] = findPar(par[x.fi][x.se]));
}

void mergePoints(pii x, pii y) {
    x = findPar(x);
    y = findPar(y);
    if (x != y) {
        par[y.fi][y.se] = x;
    }
}

void initLR() {
    for (int i = 1; i <= q; i++) {
        L[i] = 1;
        R[i] = MAXH;

        if (Q[i].x == Q[i].y) {
            L[i] = R[i] = V[Q[i].x.fi][Q[i].x.se];
        }
    }
}

bool isExistRemainingQuestion() {
    for (int i = 1; i <= q; i++) {
        if (L[i] < R[i]) {
            return true;
        }
    }
    return false;
}

void initJobs() {
    jobs.clear();
    for (int i = 1; i <= q; i++) {
        if (L[i] >= R[i]) {
            continue;
        }
        M[i] = (L[i] + R[i]) >> 1;
        jobs.pb(Jobs(M[i], i));
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            jobs.pb(Jobs(V[i][j], pii(i, j)));
        }
    }
}


void initPar() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            par[i][j] = pii(i, j);
        }
    }
}

void initIsConnedted() {
    for (int i = 1; i <= q; i++) {
        isConnected[i] = false;
    }
}

bool isInVaildRange(pii cor) {
    if (cor.fi > m || cor.se > n || cor.fi < 1 || cor.se < 1) {
        return false;
    }
    return true;
}

void calcPoint(int val, pii cor) {
    for (int i = 0; i < 4; i++) {
        pii newCor = pii(cor.fi + dxy[i].fi, cor.se + dxy[i].se);
        if (!isInVaildRange(newCor) || val < V[newCor.fi][newCor.se]) {
            continue;
        }
        mergePoints(cor, newCor);
    }
}

void calcQuery(int val, int queryIdx) {
    pii x = findPar(Q[queryIdx].x);
    pii y = findPar(Q[queryIdx].y);
    isConnected[queryIdx] = (x == y);
}

void calc() {
    for (Jobs job: jobs) {
        if (job.type == 0) { // point
            calcPoint(job.val, job.cor);
        }
        else { // query
            calcQuery(job.val, job.queryIdx);
        }
    }
}

void updateLR() {
    for (int i = 1; i <= q; i++) {
        if (L[i] == R[i]) {
            continue;
        }

        if (isConnected[i]) {
            R[i] = M[i];
        }
        else {
            L[i] = M[i] + 1;
        }
    }
}

void parallelBinarySearch() {

    initLR();

    bool isAllQuestionDone = false;
    while(isExistRemainingQuestion()) {
        initJobs();
        initPar();
        initIsConnedted();

        sort(all(jobs), [&](const Jobs x, const Jobs y) {
            if (x.val == y.val) {
                return x.type < y.type;
            }
            return x.val < y.val;
        });

        calc();
        updateLR();
    }

    for (int i = 1; i <= q; i++) {
        resHeight[i] = L[i];
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &m, &n, &q);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &V[i][j]);
        }
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d %d %d %d", &Q[i].x.fi, &Q[i].x.se, &Q[i].y.fi, &Q[i].y.se);
    }

    parallelBinarySearch();

    for (int i = 1; i <= q; i++) {
        printf("%d\n", resHeight[i]);
    }
    return 0;
}