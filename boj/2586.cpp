#include<bits/stdc++.h>
using namespace std;
const int MAXP = 100005;
const int MAXF = 100005;
stack<int> stP, stF;
int p, f;
int P[MAXP], F[MAXF];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &p, &f);
    for (int i = 0; i < p; i++) {
        scanf("%d", &P[i]);
    }

    for (int i = 0; i < f; i++) {
        scanf("%d", &F[i]);
    }

    int res = 0;

    for (int i = 0, j = 0; i < p || j < f;) {
        if (j == f || (i != p && P[i] <= F[j])) {
            stP.push(P[i]);
            i++;
        }
        else {
            stF.push(F[j]);
            j++;
        }
        while (stP.size() && stF.size()) {
            res += abs(stP.top() - stF.top());
            stP.pop();
            stF.pop();
        }
    }

    printf("%d\n", res);
    return 0;
}