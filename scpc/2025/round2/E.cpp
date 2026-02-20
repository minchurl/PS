#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int N, Q;
char S[MAXN];
int cnt[MAXN];
int mc;
void update(int j, int c) {
    if (cnt[j] == 0 && c == -1) {
        mc++;
    }
    else if (cnt[j] == -1 && c == 1) {
        mc--;
    }
    cnt[j] += c;
}
int main() {
    setbuf(stdout, NULL);
    int T;
    scanf("%d", &T);
    for (int TC = 1; TC <= T; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &N, &Q);
        scanf("%s", S + 1);
        cnt[0] = 0;
        mc = 0;
        for (int i = 1; i <= N; i++) {
            if (S[i] == 'B') {
                cnt[i] = cnt[i - 1] + 1;
            }
            else if (S[i] == 'C') {
                cnt[i] = cnt[i - 1] - 1;
            }
            if (cnt[i] < 0) {
                mc++;
            }
        }
        printf("%s\n", mc == 0 ? "YES" : "NO");
        for (int i = 0; i < Q; i++) {
            int j;
            scanf("%d", &j);
            if (S[j] == 'B') {
                update(j, -1);
            }
            if (S[j] == 'C') {
                update(j, 1);
            }
            if (S[j + 1] == 'C') {
                update(j, -1);
            }
            if (S[j + 1] == 'B') {
                update(j, 1);
            }

            swap(S[j], S[j + 1]);
            printf("%s\n", mc == 0 ? "YES" : "NO");
        }
    }
}