#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 55;
const int MAXM = 2000;
int n, arr[MAXN];
int A[MAXN], B[MAXN];
bool is_visited[MAXN];
bool is_prime[MAXM + 5];
vector<int> adj[MAXN];
vector<int> res;
void construct_is_prime() {
    is_prime[2] = is_prime[3] = true;
    for (int i = 5; i <= MAXM; i += 2) {
        int e = sqrt(i);
        is_prime[i] = true;
        for (int j = 3; j <= e; j += 2) {
            if (i % j == 0) {
                is_prime[i] = false;
                break;
            }
        }
    }
}
void init_match() {
    for (int i = 1; i <= n; i++) {
        A[i] = B[i] = 0;
    }
}
void init_is_visited() {
    for (int i = 1; i <= n; i++) {
        is_visited[i] = false;
    }
}
bool matching(int u) {
    is_visited[u] = true;
    for (int v: adj[u]) {
        if (!B[v] || (!is_visited[B[v]] && matching(B[v]))) {
            A[u] = v;
            B[v] = u;
            return true;
        }
    }
    return false;
}
int main() {
    construct_is_prime();
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        cnt += (arr[i] % 2) ? 1 : -1;
        for (int j = 1; j < i; j++) {
            if (is_prime[arr[i] + arr[j]]) {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }

    if (cnt != 0) {
        printf("-1\n");
        return 0;
    }

    for (int i: adj[1]) {
        init_match();
        A[1] = i;
        B[i] = 1;


        bool is_possible = true;

        for (int j = 2; j <= n; j++) {
            if (arr[1] % 2 != arr[j] % 2 || A[j]) {
                continue;
            }
            init_is_visited();
            is_visited[1] = is_visited[i] = true;
            if (!matching(j)) {
                is_possible = false;
            }
        }
        if (is_possible) {
            res.pb(arr[i]);
        }
    }

    sort(all(res));
    if (res.size() == 0) {
        printf("-1\n");
    }
    else {
        for (int v: res) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}