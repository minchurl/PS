#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n;
int A[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &A[i]);
    }
    sort(A + 1, A + n + 1);

    return 0;
}