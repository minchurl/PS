#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
int n, k;
int f[MAXN];
int a[2 * MAXN];
int b[MAXN];
void make_f() {
    int i, j;
    f[i = 0] = j = -1;
    while (i < n) {
        while (j != -1 && b[i] != b[j]) {
            j = f[j];
        }
        i++;
        j++;
        f[i] = j;
    }
}

bool kmp() {
    int i, j;
    bool res = false;
    i = j = -1;
    while (i < 2 * n) {
        while (j != -1 && a[i] != b[j]) {
            j = f[j];
        }
        i++;
        j++;
        if (j == n) {
            j = f[j];
            if (i == 2 * n && k != 1) {
                res = true;
            }
            if (i != 2 * n && k % 2 != 0) {
                res = true;
            }
            if (i != 2 * n && k % 2 == 0 && k != 0 && n > 2) {
                res = true;
            }
        }
    }
    return res;
}

int main() {
    freopen("consecutive_cuts_chapter_1_validation_input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int TC;
    scanf("%d", &TC);
    for (int TI = 1; TI <= TC; TI++) {
        printf("Case #%d: ", TI);
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            a[i + n] = a[i];
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }
        make_f();
        printf("%s\n", kmp() ? "YES" : "NO");
    }
    return 0;
}