#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int n, k;
int yut_list[MAXN];
int dest[MAXN];
long long last_loc[MAXN], last_cnt[MAXN];
int yut_next(int curr, int yut) {
    if (curr == 5) {
        return 20 + yut;
    }
    if (curr == 10) {
        return 25 + yut;
    }
    if (curr == 23) {
        curr = 28;
    }
    if (curr >= 21 && curr <= 25) {
        return (curr + yut > 25) ? curr + yut - 11 : curr + yut;
    }
    if (curr >= 26 && curr <= 30) {
        if (curr + yut > 31) {
            return -1;
        }
        if (curr + yut == 31) {
            return 20;
        }
        return curr + yut;
    }
    if (curr + yut >= 21) {
        return -1;
    }
    return curr + yut;
}
int construct_dest(int st) {
    int d = 0;
    int curr = 0;
    while (curr != -1) {
        curr = yut_next(curr, yut_list[(st + d) % n]);
        d++;
    }
    return d;
}
void construct_dest() {
    for (int i = 0; i < n; i++) {
        dest[i] = construct_dest(i);
    }
}
void init() {
    for (int i = 0; i < n; i++) {
        last_loc[i] = -1;
    }
}
long long calc() {
    long long cnt = 0;
    long long curr = 0;
    long long ed = (long long)n * k;

    long long mega_diff, mega_cnt, mega_repeat;

    // first phase
    last_loc[curr % n] = curr;
    last_cnt[curr % n] = cnt;
    bool chk = false;
    while (curr + dest[curr % n] <= ed) {

        curr += dest[curr % n];
        cnt++;

        if (!chk && last_loc[curr % n] != -1) {
            mega_diff = curr - last_loc[curr % n];
            mega_cnt = cnt - last_cnt[curr % n];
            mega_repeat = (ed - curr) / mega_diff;


            cnt = cnt + mega_cnt * mega_repeat;
            curr = curr + mega_diff * mega_repeat;
            chk = true;

        }
        if (!chk) {
            last_loc[curr % n] = curr;
            last_cnt[curr % n] = cnt;
        }
    }

    return cnt;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TN;
    scanf("%d", &TN);

    for (int TC = 1; TC <= TN; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &yut_list[i]);
        }
        init();
        construct_dest();
        printf("%lld\n", calc());
    }
    return 0;
}