#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1005;
struct node {
    int i;
    int r;
    int c;
};
node arr[2][2];
int n, q;
int org[MAXN][MAXN];
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            org[i][j] = n * i + j + 1;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            arr[i][j].i = 2 * i + j;
        }
    }

    while (q--) {
        char type[4];
        scanf("%s", type);
        if (type[0] == 'R') {
            if (type[1] == 'O') {
                arr[0][0].c++;
                arr[0][1].c++;
                swap(arr[0][0], arr[0][1]);
            }
            else {
                arr[1][0].c++;
                arr[1][1].c++;
                swap(arr[1][0], arr[1][1]);
            }
        }
        else if (type[0] == 'C') {
            if (type[1] == 'O') {
                arr[0][0].r++;
                arr[1][0].r++;
                swap(arr[0][0], arr[1][0]);
            }
            else {
                arr[0][1].r++;
                arr[1][1].r++;
                swap(arr[0][1], arr[1][1]);
            }
        }
        else {
            int xr, xc, yr, yc;
            scanf("%d %d %d %d", &xr, &xc, &yr, &yc);
            xr--;xc--;yr--;yc--;
            int oxr = ((xr - arr[xr % 2][xc % 2].r) % n + n) % n;
            int oxc = ((xc - arr[xr % 2][xc % 2].c) % n + n) % n;

            int oyr = ((yr - arr[yr % 2][yc % 2].r) % n + n) % n;
            int oyc = ((yc - arr[yr % 2][yc % 2].c) % n + n) % n;



            swap(org[oxr][oxc], org[oyr][oyc]);
        }
    }


    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int org_r = ((r - arr[r % 2][c % 2].r) % n + n) % n;
            int org_c = ((c - arr[r % 2][c % 2].c) % n + n) % n;
            printf("%d ", org[org_r][org_c]);
        }
        printf("\n");
    }
    return 0;
}