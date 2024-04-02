#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int n;
int sum[MAXN];
char s[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + (s[i] == 'S' ? 1 : 0);
    }


    for (int k = 1; k <= n; k++) {
        int i = 0;
        int cnt = 0;
        int res = 0;
        while (cnt < k && i + k - cnt <= n) {
            i += k - cnt;
            cnt = sum[i];
            res++;
        }
        printf("%d ", res);
    }
    printf("\n");
    return 0;
}