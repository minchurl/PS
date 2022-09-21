#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef pair<int, int> pii;

const int MAXR = 3005;
const int MAXC = 3005;
int r, c;
bool blocked[MAXR][MAXC];
char paint[MAXR][MAXC];
bool isInBoundary(int i, int j) {
    if (i < 1 || j < 1 || i > r || j > c) {
        return false;
    }
    return true;
}
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int countNotBlocked(int x, int y) {
    int res = 0;
    for (int i = 0; i < 4; i++) {
        int ax = x + dx[i];
        int ay = y + dy[i];
        if (isInBoundary(ax, ay) && !blocked[ax][ay]) {
            res++;
        }
    }
    return res;
}
queue<pii> Q;
void get_blocked() {
    // init Q
    while (Q.size()) {
        Q.pop();
    }

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (blocked[i][j] || countNotBlocked(i, j) < 2) {
                blocked[i][j] = true;
                Q.push(pii(i, j));
            }
        }
    }

    // get blocked
    while(Q.size()) {
        pii p = Q.front(); Q.pop();
        for (int i = 0; i < 4; i++) {
            pii q = pii(p.fi + dx[i], p.se + dy[i]);
            if (isInBoundary(q.fi, q.se) && !blocked[q.fi][q.se] && countNotBlocked(q.fi, q.se) < 2) {
                blocked[q.fi][q.se] = true;
                Q.push(q);
            }
        }
    }
}

bool isPossible() {
    for(int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (paint[i][j] == '^' && blocked[i][j]) {
                return false;
            }
        }
    }
    return true;
}


int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d: ", TI);

        // input
        scanf("%d %d", &r, &c);
        for (int i = 1; i <= r; i++) {
            scanf("%s", paint[i] + 1);
            for (int j = 1; j <= c; j++) {
                if (paint[i][j] == '#') {
                    blocked[i][j] = true;
                }
                else {
                    blocked[i][j] = false;
                }
            }
        }

        // solve
        get_blocked();
        if (!isPossible()){
            printf("Impossible\n");
            continue;
        }
        printf("Possible\n");
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (paint[i][j] == '#') {
                    printf("#");
                }
                else if (blocked[i][j]) {
                    printf("%c", paint[i][j]);
                }
                else {
                    printf("^");
                }
            }
            printf("\n");
        }
    }
    return 0;
}