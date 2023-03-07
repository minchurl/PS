#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define fi first
#define se second
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<LL, LL> pll;
struct node {
    LL sum;
    int cnt;
    node *l, *r;
    node(){
        sum = 0;
        cnt = 0;
        l = r = NULL;
    }

    void update(int idx, LL p, LL c) {
        this -> sum += p * c;
        this -> cnt += c;
        if (idx < 0) {
            return;
        }

        if (p >> idx & 1) {
            // right child
            if (this -> r == NULL) {
                this -> r = new node();
            }
            (this -> r) -> update(idx - 1, p, c);
            if (this -> r -> cnt == 0) {
                delete this -> r;
                this -> r = NULL;
            }
        }
        else {
            // left child
            if (this -> l == NULL) {
                this -> l = new node();
            }
            (this -> l) -> update(idx - 1, p, c);
            if (this -> l -> cnt == 0) {
                delete this -> l;
                this -> l = NULL;
            }
        }
    }
    LL get_tallest_point(int idx) {
        if (idx < 0 || (this -> l == NULL && this -> r == NULL)) {
            return 0;
        }
        if (this -> r == NULL) {
            return (this -> l) -> get_tallest_point(idx - 1);
        }
        return (1 << idx) | ((this -> r) -> get_tallest_point(idx - 1));
    }


    // get [l, inf)
    LL get(int idx, LL l) {
        if (idx < 0) {
            return (this -> sum) - (this -> cnt) * l;
        }
        LL res = 0;
        if (l >> idx & 1) {
            if (this -> r != NULL) {
                res += (this -> r) -> get(idx - 1, l);
            }
        }
        else {
            if (this -> l != NULL) {
                res += (this -> l) -> get(idx - 1, l);
            }

            if (this -> r != NULL) {
                res += ((this -> r) -> sum) - ((this -> r) -> cnt) * l;
            }
        }
        return res;
    }
};

struct graph_struct {
    LL tallest_point;
    LL current_minimum_point_value;
    node *root;
    void update_segment_tree(LL p, LL c) {
        root -> update(30, p, c);
    }
    LL get_current_point_value(LL p) {
        LL current_tallest_point_in_segment_tree = root -> get_tallest_point(30);
        if (p >= current_tallest_point_in_segment_tree && p <= tallest_point) {
            return current_minimum_point_value;
        }
        if (p >= tallest_point) {
            return current_minimum_point_value + abs(p - tallest_point);
        }
        return root -> get(30, p) + current_minimum_point_value;
    }
    void init_graph_struct(LL first_c) {
        root = new node();
        update_segment_tree(first_c, 1);
        tallest_point = first_c;
        current_minimum_point_value = 0;
    }

    void update_c(LL c) {
        LL current_tallest_point_in_segment_tree = root -> get_tallest_point(30);
        if (current_tallest_point_in_segment_tree <= c) {
            // next tallest point -> c
            update_segment_tree(c, 1);
            tallest_point = c;
        }
        else {
            // next tallest point -> current_tallest_point_in_segment_tree
            // current_minimum_point -> tallest_point
            current_minimum_point_value = get_current_point_value(tallest_point) + abs(c - tallest_point);
            update_segment_tree(current_tallest_point_in_segment_tree, -1);
            tallest_point = current_tallest_point_in_segment_tree;
            update_segment_tree(c, 2);
        }
    }
}graph;

int n;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    LL a, c;
    scanf("%lld", &a);
    c = a + n;
    graph.init_graph_struct(c);
    for (int i = 1; i < n; i++) {
        scanf("%lld", &a);
        c = a + n - i;
        graph.update_c(c);
    }
    printf("%lld\n", graph.current_minimum_point_value);
    return 0;
}