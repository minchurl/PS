#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int MAXN = 205;
const LL mod = 100000;
int n;
LL V[MAXN];
LL O[MAXN][MAXN], D[MAXN][MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    char in[MAXN];
    scanf("%d", &n);
    scanf("%s", in + 1);

    if (n % 2) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (in[i] == '(') {
            V[i] = -1;
        }
        else if (in[i] == '[') {
            V[i] = -2;
        }
        else if (in[i] == '{') {
            V[i] = -3;
        }
        else if (in[i] == ')') {
            V[i] = 1;
        }
        else if (in[i] == ']') {
            V[i] = 2;
        }
        else if (in[i] == '}') {
            V[i] = 3;
        }
        O[i][i - 1] = 1;
    }

    for (int len = 2; len <= n; len += 2) {
        for (int l = 1; l <= n - len + 1; l++) {
            int r = l + len - 1;
            // (O or D), [O or D], {O or D} -> O'
            if (V[l] + V[r] == 0) {
                // ? " " ? or ( " " ) ...
                if (V[l] == 0) {
                    // ? " " ?
                    O[l][r] += 3 * (O[l + 1][r - 1] + D[l + 1][r - 1]);
                }
                else if (V[l] < 0) {
                    // ( " " ) ...
                    O[l][r] += O[l + 1][r - 1] + D[l + 1][r - 1];
                }
            }
            else if (V[l] * V[r] == 0 && (V[l] < 0 || V[r] > 0)) {
                // ? " " ) ...
                O[l][r] += O[l + 1][r - 1] + D[l + 1][r - 1];
            }

            // D O or O O -> D'
            for (int k = l + 1; k < r; k += 2) {
                D[l][r] += D[l][k] * O[k + 1][r] + O[l][k] * O[k + 1][r];
            }

            if (O[l][r] >= mod) {
                O[l][r] = O[l][r] % mod + mod;
            }

            if (D[l][r] >= mod) {
                D[l][r] = D[l][r] % mod + mod;
            }
        }
    }

    LL res = O[1][n] + D[1][n];
    if (res >= mod) {
        printf("%.5lld\n", res % mod);
    }
    else {
        printf("%lld\n", res);
    }
    return 0;
}