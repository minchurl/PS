#include<bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define pb push_back
using namespace std;
const int MAXN = 305;
const int MAXM = 50005;
struct Party {
    int cnt;
    int idx;
    Party() {

    }
    Party(int _cnt, int _idx) {
        cnt = _cnt;
        idx = _idx;
    }
}party[MAXN];
bool dp[MAXM];
int n;
int from[MAXM];
int res;
int sum;
vector<int> res_list;
void generate_res_list(int i, int last) {
    res_list.clear();
    res_list.pb(last);
    while (i) {
        Party p = party[from[i]];
        res_list.pb(p.idx);
        i -= p.cnt;
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        party[i] = Party(x, i);
    }
    sort(party + 1, party + n + 1, [&](const Party x, const Party y) {
        return x.cnt > y.cnt;
    });
    dp[0] = true;
    for (int i = 1; i <= n; i++) {
        Party p = party[i];
        int j = sum / 2;
        for (; j >= 0; j--) {
            if (dp[j]) {
                break;
            }
        }
        if (j + p.cnt > sum / 2 && j + p.cnt > res) {
            res = j + p.cnt;
            generate_res_list(j, p.idx);
        }

        for (j = sum / 2 - p.cnt; j >= 0; j--) {
            if (dp[j] && !dp[j + p.cnt]) {
                dp[j + p.cnt] = true;
                from[j + p.cnt] = i;
            }
        }
    }
    sort(all(res_list));
    printf("%d\n", res_list.size());
    for (int p: res_list) {
        printf("%d ", p);
    }
    printf("\n");
    return 0;
}