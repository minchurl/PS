#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int arr[MAXN];
int main() {
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        int remain_500 = 0;
        int remain_1000 = 0;
        int remain_5000 = 0;
        int n;
        scanf("%d", &n);
        int res = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < n; i++) {
            int x = arr[i];
            if (x == 5000) {
                remain_5000++;
            }
            else if (x == 1000) {
                remain_1000++;
            }
            else {
                remain_500++;
            }
            x -= 500;
            int use_remain_1000_count = min(remain_1000, x / 1000);
            x -= use_remain_1000_count * 1000;
            remain_1000 -= use_remain_1000_count;

            int use_remain_500_count = min(remain_500, x / 500);
            x -= use_remain_500_count * 500;
            remain_500 -= use_remain_500_count;

            if (x != 0) {
                break;
            }
            else {
                res++;
            }
        }
        printf("%d\n", res);
        fflush(stdout);
    }
    return 0;
}