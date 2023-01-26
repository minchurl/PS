#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define square(x) ((x) * (x))
using namespace std;

typedef long long LL;

struct Point {
    LL x, y;

    Point(LL x = 0, LL y = 0)
        : x(x), y(y)
    {}

    Point& operator = (const Point& d) {
        x = d.x;
        y = d.y;
        return *this;
    }

    Point operator + (const Point& d) const {
        return Point(x + d.x, y + d.y);
    }

    Point operator * (const Point &d) const {
        return Point(x * d.x, y * d.y);
    }

    Point operator - (const Point &d) const {
        return Point(x - d.x, y - d.y);
    }

    bool operator == (const Point &d) const {
        return (x == d.x && y == d.y);
    }

    bool operator < (const Point &d) const {
        return (x == d.x) ? (y < d.y) : (x < d.x);
    }
};
vector<Point> lst;

int n;

LL squareDistance(Point p, Point q) {
    return square(p.x - q.x) + square(p.y - q.y);
}

double distance(Point p, Point q) {
    return sqrt(squareDistance(p, q));
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        lst.pb(Point(x, y));
    }

    sort(all(lst)); lst.erase(unique(all(lst)), lst.end());
    n = lst.size();

    if (n == 1) {
        return !printf("0\n");
    }
    if (n == 2) {
        return !printf("%.2lf\n", distance(lst[0], lst[1]));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = 0;
            for (; k < n; k++) {
                if (i == k || j == k) {
                    continue;
                }
            }
            if ()
        }
    }
    return 0;
}