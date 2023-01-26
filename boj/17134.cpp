#include<bits/stdc++.h>
using namespace std;

typedef long long lint;

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
 
namespace fft{
    using real_t = long double;
    using base = complex<real_t>;

    void fft(vector<base> &a, bool inv){
        int n = a.size(), j = 0;
        vector<base> roots(n/2);
        for(int i=1; i<n; i++){
            int bit = (n >> 1);
            while(j >= bit){
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if(i < j) swap(a[i], a[j]);
        }
        real_t ang = 2 * acos(real_t(-1)) / n * (inv ? -1 : 1);
        for(int i=0; i<n/2; i++){
            roots[i] = base(cos(ang * i), sin(ang * i));
        }
        for(int i=2; i<=n; i<<=1){
            int step = n / i;
            for(int j=0; j<n; j+=i){
                for(int k=0; k<i/2; k++){
                    base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
                    a[j+k] = u+v;
                    a[j+k+i/2] = u-v;
                }
            }
        }
        if(inv) for(int i=0; i<n; i++) a[i] /= n;
    }
    template<typename T>
    vector<T> multiply(vector<T> &v, const vector<T> &w){ // 계수가 v와 w인 함수를 곱한다
        vector<base> fv(all(v)), fw(all(w));
        int n = 2;
        while(n < sz(v) + sz(w)) n <<= 1;
        fv.resize(n); fw.resize(n);
        fft(fv, 0); fft(fw, 0);
        for(int i=0; i<n; i++) fv[i] *= fw[i];
        fft(fv, 1);
        vector<T> ret(n);
        for(int i=0; i<n; i++) ret[i] = (T)llround(fv[i].real());
        return ret;
    }
}

const int MAXN = 1000000;
bool chk[MAXN + 5];
vector<int> a, b;
vector<int> res;
int main() {
    freopen("input.txt", "r",stdin);

    a.resize(MAXN / 2 + 1);
    b.resize(MAXN / 2 + 1);
    a[2] = 1;

    for (int i = 3; i <= MAXN; i += 2) {
        if (chk[i]) {
            continue;
        }
        if (2 * i <= MAXN) {
            a[i] = 1;
        }
        b[(i + 1) / 2] = 1;

        for (int j = 2 * i; j <= MAXN; j += i) {
            chk[j] = true;
        }
    }

    res = fft::multiply(a, b);

    int T; 
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", res[(n + 1) / 2]);
    }

    return 0;
}

