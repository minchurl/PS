#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 505;
const int MAXM = 505;
const int MAXK = 505;
int n, m, k;
char s[MAXN][MAXM];
int cnt[MAXK][MAXK][26];
int rep[MAXK][MAXK];
int res;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        for (int j = 0; j < m; j++) {
            cnt[i % k][j % k][s[i][j] - 'A']++;
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            for (int h = 0; h < 26; h++) {
                if (cnt[i][j][rep[i][j]] < cnt[i][j][h]) {
                    rep[i][j] = h;
                }
            }

            for (int h = 0; h < 26; h++) {
                if (rep[i][j] != h) {
                    res += cnt[i][j][h];
                }
            }
        }
    }
    printf("%d\n", res);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", 'A' + rep[i % k][j % k]);
        }
        printf("\n");
    }
    return 0;
}