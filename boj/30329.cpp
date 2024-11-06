#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5000005;
int n;
char s[MAXN];
int main() {
    scanf("%s", s);
    n = strlen(s);
    int res = 0;
    for (int i = 0; i < n - 3; i++) {
        if (s[i + 0] == 'k' && s[i + 1] == 'i' && s[i + 2] == 'c' && s[i + 3] == 'k') {
            res++;
        }
    }
    printf("%d\n", res);
    return 0;
}