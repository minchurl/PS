#include<bits/stdc++.h>
#define MOD(x) ((x) % mod)
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pil;
const int MAXN = 100005;
const int mod = 1000000007;
struct SegTree{
    int l, r;
    int sum;
}segTree[4 * MAXN];

struct Command {
    int type;
    int value;
    Command() {

    }
    Command(int _type, int _value) {
        type = _type;
        value = _value;
    }
};
vector<Command> commandList[4 * MAXN];
int n;

void initSegTree(int here, int l, int r) {
    segTree[here].l = l;
    segTree[here].r = r;
    segTree[here].sum = 0;
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;

    initSegTree(2 * here, l, mid);
    initSegTree(2 * here + 1, mid + 1, r);
}

void clearCommandList(int here) {
    commandList[here].clear();
    commandList[here].resize(0);
}
void executeCommandList(int here) {
    for (Command command: commandList[here]){
        if (command.type == 1) {
            segTree[here].sum = MOD(segTree[here].sum + (segTree[here].r - segTree[here].l + 1) * command.value);
        }
        if (command.type == 2) {
            segTree[here].sum = MOD(segTree[here].sum * command.value);
        }
        if (command.type == 3) {
            segTree[here].sum = MOD((segTree[here].r - segTree[here].l + 1) * command.value);
        }
    }
    clearCommandList(here);
}

void updateCommandList(int here, int queryType, int value) {
    if (queryType == 3) {
        clearCommandList(here);
    }
    commandList[here].pb(Command(queryType, value));
}

void updateCommandList(int here, Command command) {
    updateCommandList(here, command.type, command.value);
}

void updateCommandList(int here, int target) {
    for (Command command: commandList[here]) {
        updateCommandList(target, command);
    }
}

void spread(int here) {
    if (segTree[here].l != segTree[here].r) {
        updateCommandList(here, 2 * here);
        updateCommandList(here, 2 * here + 1);
    }
    executeCommandList(here);
}

void updateSegTree(int here, int s, int e, int queryType, int value) {
    int l = segTree[here].l;
    int r = segTree[here].r;
    if (l > r) {
        return;
    }
    spread(here);

    if (e < l || s > r) {
        return;
    }

    if (s <= l && r <= e) {
        updateCommandList(here, queryType, value);
        spread(here);
        return;
    }

    int mid = (l + r) >> 1;
    updateSegTree(2 * here, s, e, queryType, value);
    updateSegTree(2 * here + 1, s, e, queryType, value);
    segTree[here].sum = MOD(segTree[2 * here].sum + segTree[2 * here + 1].sum);
}
int getResult(int here, int s, int e) {
    int l = segTree[here].l;
    int r = segTree[here].r;
    if (l > r) {
        return 0;
    }
    spread(here);
    if (e < l || s > r) {
        return 0;
    }

    if (s <= l && r <= e) {
        return segTree[here].sum;
    }
    int mid = (l + r) >> 1;
    return MOD(getResult(2 * here, s, e) + getResult(2 * here + 1, s, e));
}
int main() {
    freopen("input.txt","r",stdin);
    scanf("%d", &n);
    initSegTree(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        updateSegTree(1, i, i, 3, x);
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int type;
        scanf("%d", &type);
        if (type == 4) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", getResult(1, x, y));
        }
        else {
            int x, y, v;
            scanf("%d %d %d", &x, &y, &v);
            updateSegTree(1, x, y, type, v);
        }
    }
    return 0;
}