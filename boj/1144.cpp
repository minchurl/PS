#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10;
const int MAXM = 10;
int n, m;
int val[MAXN][MAXM];
int vis[MAXN][MAXM], vn;
int label[MAXN][MAXM];
int par[MAXN];
int cover[MAXN];
map<int, int> dp[MAXN];

int find_par(int x) {
    return (par[x] == x) ? x : (par[x] = find_par(par[x]));
}

bool updateLabel(int currI, int preLabelDecimal, int currLabelBinary) {
    int ln = 0;
    for (int j = m - 1; j >= 0; j--) {
        // reflect preLabelDecimal into label array
        label[currI - 1][j] = preLabelDecimal % 10;
        ln = max(ln, label[currI - 1][j]);
        preLabelDecimal /= 10;

        // reflect currLabelBinary into label array
        label[currI][j] = currLabelBinary % 2;
        currLabelBinary /= 2;
    }

    // merge
    for (int i = 1; i <= ln; i++) {
        par[i] = i;
        cover[i] = m;
    }
    int x;
    for (int l = 0; l < m; l++) {
        if (label[currI][l] == 0) {
            continue;
        }
        int r = l;
        x = 0;
        do {
            if (label[currI - 1][r] != 0) {
                if (x == 0) {
                    x = label[currI - 1][r];
                }
                par[find_par(label[currI - 1][r])] = find_par(x);
            }
            r++;
        } while(r < m && label[currI][r] != 0);
        l = r;
    }

    // labeling
    x = 0;
    for (int l = 0; l < m; l++) {
        if (label[currI][l] == 0) {
            continue;
        }
        int r = l;
        int y = m;
        do {
            if (label[currI - 1][r] != 0) {
                y = cover[find_par(label[currI - 1][r])];
            }
            r++;
        } while (r < m && label[currI][r] !=0);
        r--;

        if (y == m) {
            x++;
            y = x;
        }

        for (int i = l; i <= r; i++) {
            label[currI][i] = y;
            if (label[currI - 1][i] != 0) {
                cover[find_par(label[currI - 1][i])] = y;
            }
        }
        l = r;
    }


    // validate
    for (int i = 1; i <= ln; i++) {
        if (cover[find_par(i)] == m) {
            return false;
        }
    }
    return true;
}
int getCurrLabelDecimal(int currI) {
    int res = 0;
    for (int j = 0; j < m; j++) {
        res = res * 10 + label[currI][j];
    }
    return res;
}
int getValue(int currI) {
    int res = 0;
    for (int j = 0; j < m; j++) {
        if (label[currI][j]) {
            res += val[currI][j];
        }
    }
    return res;
}
void updateDP(int currI, int currLabelDecimal, int value) {
    if (dp[currI].find(currLabelDecimal) != dp[currI].end() && dp[currI][currLabelDecimal] <= value) {
        return;
    }
    dp[currI][currLabelDecimal] = value;
}
int ans;
void updateAns(int currI, int value) {
    bool isReflect = true;
    for (int j = 0; j < m; j++) {
        if (label[currI][j] != 0 && label[currI][j] != 1) {
            isReflect = false;
            break;
        }
    }
    if (isReflect) {
        ans = min(ans, value);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &val[i][j]);
        }
    }
    dp[0][0] = 0;


    for (int i = 1; i <= n; i++) {
        for (int currLabelBinary = 0; currLabelBinary < (1 << m); currLabelBinary++) {
            for (auto pre: dp[i - 1]) {
                if (updateLabel(i, pre.first, currLabelBinary) == false) {
                    continue;
                }
                int currLabelDecimal = getCurrLabelDecimal(i);
                int value = getValue(i) + pre.second;
                updateAns(i, value);

                if (pre.first != 0 && currLabelDecimal == 0) {
                    continue;
                }
                updateDP(i, currLabelDecimal, value);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}