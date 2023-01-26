#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int MAXN = 15005;
const int MAXM = 1505;
int n, m;
int sum[MAXN][MAXM];
char s[MAXM];
vector<int> up, down, lst;
int main() {

    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);

    int res = 0;

    for (int i = 1; i <= m; i++) {
        lst.pb(i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%s", s + 1);

        for (int j: lst) {
            if (s[j] == '0') {
                sum[i][j] = 0;
                down.pb(j);
            }
            else {
                sum[i][j] = sum[i - 1][j] + 1;
                up.pb(j);
            }
        }
        lst.clear();

        for (int j: down) {
            lst.pb(j);
        }

        for (int j: up) {
            lst.pb(j);
        }

        for (int k = m - 1; k >= 0; k--){
            int j = lst[k];
            res = max(res, (m - k) * sum[i][j]);
        }

        up.clear();
        down.clear();
    }


    printf("%d\n", res);
    return 0;
}