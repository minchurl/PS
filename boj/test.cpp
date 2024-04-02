#include<bits/stdc++.h>
using namespace std;
const int MAXN = 15;
struct Block {
    int prop;
    int price;
    bool is_buyed;
}block[4 * MAXN];
struct Gold {
    int prop;
    int val;
}gold[4 * MAXN];
int n, G, S, W;
int g;
int m;
int walfare_sum;
int curr;
int cnt;

void moving(int x, int y) {
    // curr == n - 1
    if (block[curr].prop == 1 && cnt < 3) {
        cnt++;
        if (x == y) {
            cnt = 3;
        }
        return;
    }
    cnt = 0;

    // moving
    curr += x + y;
    if (curr >= m){
        S += (curr / m) * W;
        curr %= m;
    }
}

void event() {
    if (block[curr].prop < 4) {
        if (block[curr].prop == 2) {
            S += walfare_sum;
            walfare_sum = 0;
        }
        else if (block[curr].prop == 3) {
            S += W;
            curr = 0;
        }
        return;
    }

    if (block[curr].prop == 4) {
        if (block[curr].is_buyed || S < block[curr].price) {
            return;
        }
        block[curr].is_buyed = true;
        S -= block[curr].price;
        return;
    }
    if (gold[g].prop == 1) {
        S += gold[g].val;
        g = (g + 1) % G;
    }
    else if (gold[g].prop == 2) {
        S -= gold[g].val;
        if (S < 0) {
            printf("LOSE\n");
            exit(0);
        }
        g = (g + 1) % G;
    }
    else if (gold[g].prop == 3) {
        S -= gold[g].val;
        walfare_sum += gold[g].val;
        if (S < 0) {
            printf("LOSE\n");
            exit(0);
        }
        g = (g + 1) % G;
    }
    else {
        moving(gold[g].val, 0);
        g = (g + 1) % G;
        event();
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d %d", &n, &S, &W, &G);
    m = 4 * (n - 1);

    for (int i = 0; i < G; i++) {
        scanf("%d %d", &gold[i].prop, &gold[i].val);
    }

    for (int i = 0; i < m; i++) {
        if (i % (n - 1) == 0) {
            block[i].prop = i / (n - 1);
            continue;
        }
        char s[2];
        scanf("%s", s);
        if (s[0] == 'L') {
            block[i].prop = 4;
            scanf("%d", &block[i].price);
        }
        else {
            block[i].prop = 5;
        }
    }
    int I;
    scanf("%d", &I);
    for (int i = 0; i < I; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        moving(x, y);
        event();
    }

    for (int i = 0; i < m; i++) {
        if (block[i].prop == 4 && block[i].is_buyed == false) {
            printf("LOSE\n");
            return 0;
        }
    }
    printf("WIN\n");
    return 0;
}