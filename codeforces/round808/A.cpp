#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n, q;
int a[MAXN];
bool res[MAXN];
int main() {
    freopen("input.txt","r",stdin);
    int TC;
    scanf("%d", &TC);

    while (TC--) {
        scanf("%d %d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int currQ = 0;

        for (int i = n; i >= 1; i--) {
            if (a[i] <= currQ) {
                res[i] = true;
            }
            else if (a[i] > currQ) {
                if (currQ < q) {
                    currQ++;
                    res[i] = true;
                }
                else {
                    res[i] = false;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            printf("%d", res[i]);
        }
        printf("\n");
    }
    return 0;
}