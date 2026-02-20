#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100105;
const int MAXLOGA = 29;
int N;
int A[MAXN];
struct node {
    int cnt;
    node *left, *right;
    node() {
        cnt = 0;
        left = right = NULL;
    }
    node (int _cnt, node *_l, node *_r) {
        cnt = _cnt;
        left = _l;
        right = _r;
    }
};
struct inner_seg_tree {
    node *root;
    void init() {
        root = new node();
    }
    void append(int v, node *cur, int idx) {
        cur -> cnt++;
        if (idx < 0) {
            return;
        }
        if (v >> idx & 1) {
            // right
            if (cur -> right == NULL) {
                cur -> right = new node();
            }
            append(v, cur -> right, idx - 1);
        }
        else {
            // left
            if (cur -> left == NULL) {
                cur -> left = new node();
            }
            append(v, cur -> left, idx - 1);
        }
    }
    void append(int v) {
        append(v, root, MAXLOGA);
    }
    void remove(int v, node *cur, int idx) {
        cur -> cnt--;
        if (idx < 0) {
            return;
        }
        if (v >> idx & 1) {
            // right
            remove(v, cur -> right, idx - 1);
            if (cur -> right -> cnt == 0) {
                delete cur -> right;
                cur -> right = NULL;
            }
        }
        else {
            // left
            remove(v, cur -> left, idx - 1);
            if (cur -> left -> cnt == 0) {
                delete cur -> left;
                cur -> left = NULL;
            }
        }
    }
    void remove(int v) {
        remove(v, root, MAXLOGA);
    }
    int count_query(int k, node *cur, int idx) {
        if (idx < 0) {
            return 0;
        }
        if (k >> idx & 1) {
            // right
            return (cur -> right == NULL) ? 0 : count_query(k, cur -> right, idx - 1);
        }
        else {
            // left
            return  ((cur -> right == NULL) ? 0 : cur -> right -> cnt) + 
                    ((cur -> left == NULL) ? 0 : count_query(k, cur -> left, idx - 1));
        }
    }
    int count_query(int k) {
        return count_query(k, root, MAXLOGA);
    }
};
inner_seg_tree roots[2 * MAXN];
void init_seg_tree(int u, int l, int r) {
    roots[u].init();
    for (int i = l; i <= r; i++) {
        roots[u].append(A[i]);
    }
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    init_seg_tree(2 * u, l, mid);
    init_seg_tree(2 * u + 1, mid + 1, r);
}
void init_seg_tree() {
    init_seg_tree(1, 1, N);
}
void update_seg_tree(int u, int l, int r, int i, int new_val) {
    roots[u].append(new_val);
    roots[u].remove(A[i]);
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid) {
        update_seg_tree(2 * u, l, mid, i, new_val);
    }
    else {
        update_seg_tree(2 * u + 1, mid + 1, r, i, new_val);
    }
}
void update_seg_tree(int i, int new_val) {
    update_seg_tree(1, 1, N, i, new_val);
    A[i] = new_val;
}
int get_count_query(int u, int l, int r, int st, int ed, int k) {
    if (st <= l && r <= ed) {
        return roots[u].count_query(k);
    }
    int mid = (l + r) >> 1;
    if (ed <= mid) {
        return get_count_query(2 * u, l, mid, st, ed, k);
    }
    else if (st > mid) {
        return get_count_query(2 * u + 1, mid + 1, r, st, ed, k);
    }
    else {
        return get_count_query(2 * u, l, mid, st, ed, k) +
               get_count_query(2 * u + 1, mid + 1, r, st, ed, k);
    }
}
int get_count_query(int st, int ed, int k) {
    return get_count_query(1, 1, N, st, ed, k);
}
int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    init_seg_tree();
    int M;
    scanf("%d", &M);
    while (M--) {
        int ty;
        int i, j, k;
        scanf("%d", &ty);
        if (ty == 1) {
            scanf("%d %d %d", &i, &j, &k);
            printf("%d\n", get_count_query(i, j, k));
        }
        else {
            scanf("%d %d", &i, &k);
            update_seg_tree(i, k);
        }
    }
    return 0;
}