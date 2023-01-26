#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
int n;
int loc[3][MAXN];
int res[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < 3; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
            scanf("%d", &x);
            loc[i][x] = j;
        }
    }

    for (int i = n; i >= 1; i--) {
        int j;
        int c;
        int l;
        for (j = 1; j <= n; j++) {
            c = 0;
            for (int k = 0; k < 3; k++) {
                if (loc[k][j] == i) {
                    c++;
                }
                else {
                    l = k;
                }
            }
            if (c >= 2) {
                break;
            }
        }
        res[i] = j;
        if (c == 3) {
            for (int k = 0; k < 3; k++) {
                loc[k][j] = n + 1;
            }
            continue;
        }
        for (int k = 1; k <= n; k++) {
            if (loc[l][k] > loc[l][j] && loc[l][k] <= i) {
                loc[l][k]--;
            }
        }
        for (int k = 0; k < 3; k++) {
            loc[k][j] = n + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    return 0;
}