#include<bits/stdc++.h>
#define _USE_MATH_DEFINES
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef complex<double> base;
typedef long long LL;
const int MAXN = 500005;
LL n;
vector<LL> cnt;
LL res;
 
void fft(vector<base> &a, bool invert)
{
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang), sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert){
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
 
template <typename T>
vector<T> multiply(const vector<T>& a, const vector<T>& b)
{
    vector<base> fa(all(a)), fb(all(b));
    int n = 1, m = sz(a)+sz(b)-1;
    while (n < m) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<T> ret(m);
    for (int i=0;i<m;i++) ret[i] = static_cast<T>(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
    return ret;
}
vector<LL> R;

int main() {
    scanf("%d", &n);
    cnt.resize(n);
    for (LL i = 1; i < n; i++) {
        cnt[i * i % n]++;
    }

    for (LL i = 1; i < n; i++) {
        res += cnt[i * i * 2 % n];
    }

    R = multiply(cnt, cnt);

    LL c = 0;
    for (LL i = 0; i < n; i++) {
        c += (LL)R[i] + (LL)R[n + i];
    }

    printf("%lld\n", c);



    for (LL i = 0; i < n; i++) {
        res += (R[i] + R[n + i]) * cnt[i];
    }

    printf("%lld\n", res / 2);
    return 0;
}