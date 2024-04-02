#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 25;
const int MAXM = 1048600;
int n, m;
int win_cnt[MAXM];
int losed_by[MAXM];
vector<int> lst[MAXN];
int blanked_loser;
int calc1_chk[MAXM];
int calc2_chk[MAXM];

void calc1(int i) {
    for (int x: lst[i]) {
        if (calc1_chk[losed_by[x]]) {
            printf("%d %d\n", min(x, calc1_chk[losed_by[x]]), blanked_loser);
            printf("%d %d\n", max(x, calc1_chk[losed_by[x]]), blanked_loser);
            return;
        }
        calc1_chk[losed_by[x]] = x;
    }
}

void calc2(int i) {
    for (int x: lst[i]) {
        calc2_chk[losed_by[x]]++;
    }

    i++;
    for (; i <= n; i++) {
        for (int x: lst[i]) {
            if (calc2_chk[x] == 0) {
                printf("%d %d\n", x, blanked_loser);
            }
        }
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    m = (1 << n);
    for (int i = 1; i <= m - 2; i++) {
        int w, l;
        scanf("%d %d", &w, &l);
        losed_by[l] = w;
        win_cnt[w]++;
    }

    int winner = 0;
    for (int i = 1; i <= m; i++) {
        lst[win_cnt[i]].pb(i);
        if (losed_by[i] == 0) {
            if (winner == 0) {
                winner = i;
            }
            else if (win_cnt[winner] < win_cnt[i]) {
                winner = i;
            }
            else if (win_cnt[winner] == win_cnt[i]) {
                printf("%d %d\n", winner, i);
                printf("%d %d\n", i, winner);
                return 0;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        if (i == winner) {
            continue;
        }
        if (losed_by[i] == 0) {
            blanked_loser = i;
        }
    }


    if ((1 << (n - 1 - win_cnt[blanked_loser])) < lst[win_cnt[blanked_loser]].size()) {
        calc1(win_cnt[blanked_loser]);
    }
    else {
        calc2(win_cnt[blanked_loser]);
    }

    return 0;
}