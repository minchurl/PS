#include<bits/stdc++.h>
#define pb push_back
#define all(v) (v).begin(), (v).end()
#define sq(x) ((x) * (x))
#define abs(v) ((v) > 0 ? (v) : (-(v)))
#define nxt(i) (((i) + 1) % (cn))
using namespace std;
typedef long long llint;
const llint MAXN = 1005;
struct Point {
    llint x, y;
};
llint n, cn;
vector<Point> pos, convex;
void init() {
    pos.clear();
    convex.clear();
    cn = 0;
}
llint ccw(Point p, Point q, Point r) {
    return (p.x * q.y + q.x * r.y + r.x * p.y) - (p.y * q.x + q.y * r.x + r.y * p.x);
}

vector<Point> convex_hull(vector<Point>& dat) {
    if (dat.size() <= 3) return dat;
    vector<Point> upper, lower;
    sort(dat.begin(), dat.end(), [](const Point& a, const Point& b) {
        return (a.x == b.x) ? a.y < b.y : a.x < b.x;
    });
    for (const auto& p : dat) {
        while (upper.size() >= 2 && ccw(*++upper.rbegin(), *upper.rbegin(), p) >= 0)
        upper.pop_back();
        while (lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p) <= 0)
            lower.pop_back();
        upper.emplace_back(p);
        lower.emplace_back(p);
    }
    upper.insert(upper.end(), ++lower.rbegin(), --lower.rend());

    return upper;
}


llint calc() {

    cn = convex.size();
    // rotating calipers
    if (cn < 3) {
        return 0;
    }

    if (cn == 3) {
        return abs(ccw(convex[0], convex[1], convex[2]));
    }

    if (cn == 4) {
        return abs(ccw(convex[0], convex[1], convex[2])) + abs(ccw(convex[2], convex[3], convex[0]));
    }

    llint res = 0;

    for (int p = 0; p < cn; p++) {
        // p q r s
        int q = nxt(p);
        int r = nxt(q);
        int s = nxt(r);

        for (; nxt(r) != p; r = nxt(r)) {
            abs(ccw(convex[p], convex[nxt(q)], convex[r]));
            while (abs(ccw(convex[p], convex[q], convex[r])) <= abs(ccw(convex[p], convex[nxt(q)], convex[r]))){
                q = nxt(q);
            }

            while (abs(ccw(convex[p], convex[q], convex[r])) <= abs(ccw(convex[p], convex[nxt(s)], convex[r]))){
                s = nxt(s);
            }
            res = max(res, abs(ccw(convex[p], convex[q], convex[r])) + abs(ccw(convex[p], convex[s], convex[r])));
        }
    }
    return res;
}
int main() {
    llint T;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld", &n);
        init();
        for (llint i = 0; i < n; i++) {
            llint x, y;
            scanf("%lld %lld", &x, &y);
            pos.pb({x, y});
        }

        convex = convex_hull(pos);

        llint res = calc();
        if (res % 2) {
            printf("%lld.5\n", res / 2);
        }
        else {
            printf("%lld\n", res / 2);
        }
    }
    return 0;
}