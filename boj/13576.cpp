#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int f[MAXN];
int cnt[MAXN];
bool chk[MAXN];
char s[MAXN];

int res1[MAXN], res2[MAXN], resn;

void makeF() {
    int i, j;
    i = 0;
    j = -1;
    f[i] = j;
    while (i < n) {
        while (j != -1 && s[i] != s[j]) {
            j = f[j];
        }
        i++;
        j++;
        f[i] = j;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%s", s);
    n = strlen(s);
    makeF();
    res1[resn++] = n;

    for (int i = f[n]; i > 0; i = f[i]) {
        res1[resn++] = i;
        chk[i] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (chk[f[i]]) {
            cnt[f[i]]++;
        }
    }

    int sum = 0;

    for (int i = 0; i < resn; i++) {
        sum += cnt[res1[i]];
        res2[i] = sum + 1;
    }


    printf("%d\n", resn);
    for (int i = resn - 1; i >= 0; i--) {
        printf("%d %d\n", res1[i], res2[i]);
    }
    return 0;
}