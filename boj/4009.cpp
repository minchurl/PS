#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pii;
int n, k;
bool chk[MAXN];
vector<int> adj[MAXN];
vector<int> diameter;
pii findFarVertex(int x, int par) {
	pii res = pii(0, x);
	for (int y: adj[x]) {
		if (!chk[y] && y != par) {
			pii yRes = findFarVertex(y, x);
			yRes.fi++;
			res = max(res, yRes);
		}
	}
	return res;
}
int findFarVertex(int st) {
	return findFarVertex(st, 0).se;
}
int countEdge(int x, int par, int st, int ed, bool Z) {
	int res = 0;
	for (int y: adj[x]) {
		if (!chk[y] && y != par) {
			res = max(res, countEdge(y, x, st, ed, Z));
		}
	}
	if (res || x == ed) {
		chk[x] = Z;
		if (Z) {
			diameter.pb(x);
		}
		return (x == st) ? res : res + 1;
	}
	return 0;
} 
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].pb(y);
		adj[y].pb(x);
	}

	int ans = 0;

	// k = 1
	int st = findFarVertex(1);
	int ed = findFarVertex(st);
	ans = countEdge(st, 0, st, ed, true);
	if (k == 1) {
		printf("%d\n", 2 * n - 2 + 1 - ans);
		return 0;
	}

	// k = 2
	int basis = ans;
	int shareBasis = 0;
	for (int i: diameter) {
		shareBasis--;

		chk[i] = false;
		pii temp = findFarVertex(i, 0);
		int dualSt = temp.se;
		int dualEd = findFarVertex(dualSt);
		int dualAns = basis + countEdge(dualSt, 0, dualSt, dualEd, false);

		ans = max(ans, dualAns);
		ans = max(ans, shareBasis + temp.fi + basis);
		shareBasis = max(shareBasis, temp.fi);

		chk[i] = true;
	}

	printf("%d\n", 2 * n - 2 + 2 - ans);
	return 0;
}
