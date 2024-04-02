#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
const int MAXN = 1000005;

struct node {
    int color;
    LL cnt;
    node() {
        
    }
    
    node (int _color, LL _cnt) {
        color = _color;
        cnt = _cnt;
    }
};
int n;
char in_str[MAXN];
node lst[MAXN];
int ln;
int convert(char s) {
    if (s == '(') {
        return 1;
    }
    if (s == '{') {
        return 2;
    }
    if (s == ')') {
        return -1;
    }
    return -2;
}
int main() {
    freopen("input.txt", "r", stdin);
    int TN;
    scanf("%d", &TN);

    for (int TC = 1; TC <= TN; TC++) {
        printf("Case #%d\n", TC);
        scanf("%d", &n);
        scanf("%s", in_str + 1);

        ln = 0;
        LL res = 0;
        lst[ln++] = node(0, 1);
        for (int i = 1; i <= n; i++) {
            int c = convert(in_str[i]);

            if (c > 0) {
                lst[ln++] = node(c, 1);
                continue;
            }
            if (ln < 2 || lst[ln - 1].color + c != 0) {
                // fall
                ln = 0;
                lst[ln++] = node(0, 1);
            }
            else {
                ln--;
                res += lst[ln - 1].cnt;
                lst[ln - 1].cnt++;
            }
        }

        printf("%lld\n", res);
    }
    return 0;
}