#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
const int BASE = 1005;
const int MAXN = 105;
const int MAXT = 1005;
const int inf = 0x3fffffff;
int N;
int cost[MAXT][2 * BASE];
bool prohibited[MAXT][2 * BASE];
void init_cost() {
    for (int i = 0; i < MAXT; i++) {
        for (int j = 0; j < 2 * BASE; j++) {
            cost[i][j] = inf;
        }
    }
    cost[0][BASE] = 0;
}

int calc() {
    for (int T = 1; T < MAXT; T++) {
        for (int loc = 0; loc < 2 * BASE; loc++) {
            if (prohibited[T][loc]) {
                continue;
            }
            // stay
            cost[T][loc] = cost[T - 1][loc];
            // from left
            if (loc > 0) {
                cost[T][loc] = min(cost[T][loc], cost[T - 1][loc - 1] + 1);
            }
            // from right
            if (loc < 2 * BASE - 1) {
                cost[T][loc] = min(cost[T][loc], cost[T - 1][loc + 1] + 1);
            }
        }
    }

    int res = inf;
    for (int loc = 0; loc < 2 * BASE; loc++) {
        res = min(res, cost[MAXT - 1][loc]);
    }
    return res >= inf ? -1 : res;
}
int main() {
    init_cost();
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int T, A, B;
        scanf("%d %d %d", &T, &A, &B);
        A += BASE;
        B += BASE;
        for (int j = A + 1; j < B; j++) {
            prohibited[T][j] = true;
        }
    }

    printf("%d\n", calc());
    return 0;
}