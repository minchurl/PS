#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n;
int a[MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    if (n == 1) {
        return !printf("%d\n", a[0]);
    }
    sort(a, a + n);

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    if (sum > a[n - 2] * n) {
        printf("%.6lf\n", (double)sum / n);
    }
    else {
        printf("%d\n", a[n - 2]);
    }
    return 0;
}