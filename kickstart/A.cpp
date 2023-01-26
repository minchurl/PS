#include<bits/stdc++.h>
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define mod(x) (((x) % l + l) % l)
using namespace std;
typedef long long LL;
int main() {
    freopen("input.txt","r",stdin);
    char s[3];
    LL TC;
    scanf("%lld", &TC);
    for (LL TI = 1; TI <= TC; TI++) {
        LL res = 0;
        LL n, l;
        scanf("%lld %lld", &l, &n);
        LL curr = 0, currDir = 0;
        for (LL i = 0; i < n; i++) {
            LL amount;
            scanf("%lld %s", &amount, s);
            LL dir = s[0] - 'B';
            LL currRes = 0;
            if (dir + currDir == 0) {
                currRes--;
            }

            if (dir == 1) {
                if (curr + amount >= l || curr == 0) {
                    currDir = dir;
                }
                currRes += (curr + amount) / l;
                curr = (curr + amount) % l;
            }
            else {
                if (curr - amount <= 0) {
                    currDir = dir;
                }

                currRes += (((l - curr) % l) + amount) / l;
                curr = mod(curr - amount);
            }
            res += max(currRes, (LL)0);

        }
        printf("Case #%lld: %lld\n", TI, res);
    }
    return 0;
}