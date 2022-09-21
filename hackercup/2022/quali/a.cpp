#include<bits/stdc++.h>
using namespace std;
int cnt[105];
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int TC;
    scanf("%d", &TC);
    for(int TI = 1; TI <= TC; TI++) {
        int n, k;
        bool res = true;
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= 100; i++) {
            cnt[i] = 0;
        }

        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            cnt[x]++;
            if (cnt[x] > 2) {
                res = false;
            }
        }
        if (2 * k < n) {
            res = false;
        }
        printf("Case #%d: %s\n", TI, res ? "YES" : "NO");
    }
    return 0;
}