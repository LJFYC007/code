#include <bits/stdc++.h>
using namespace std;

//就暂且这么认为吧
typedef long long int64;
const int mod = 998244353 , g = 3;
namespace SYT_POLY
{

int _[1<<19] , w0[1<<19] , w1[1<<19];//备用的数组

int qpow(int x , int y = mod - 2)
{
    int res = 1;
    for(; y ; y >>= 1 , x = 1ll * x * x % mod)
        if(y & 1) res = 1ll * res * x % mod;
    return res; 
} 

struct Poly : public vector<int>
{
    int degree() {return (int)size() - 1;}
    void set(int deg) {resize(deg + 1);}
    int val(int x)//单点求值
    {
        int res = 0;
        for(int i = degree() ; ~i ; i--)
            res = (1ll * res * x + this->at(i)) % mod;
        return res;
    }
};

//加法
Poly operator + (Poly a , Poly b)
{
    a.set(max(a.degree() , b.degree()));
    for(int i = 0 ; i <= b.degree() ; i ++) a[i] = (a[i] + b[i]) % mod;
    return a;
}
//减法
Poly operator - (Poly a , Poly b)
{
    a.set(max(a.degree() , b.degree()));
    for(int i = 0 ; i <= b.degree() ; i ++) a[i] = (a[i] - b[i] + mod) % mod;
    return a;
}

//准备备用数组，计算limit
int ntt_prepare(int deg)
{
    int limit = 1;
    while(limit <= deg) limit <<= 1;
    for(int i = 1 ; i < limit ; i++)
    {
        _[i] = _[i >> 1] >> 1;
        if(i&1) _[i] |= (limit >> 1);
    }
    w0[0] = w1[0] = 1;
    int wn = qpow(g , (mod-1) / limit);
    for(int i = 1 ; i < limit ; i++) 
        w0[limit - i] = w1[i] = 1ll * w1[i-1] * wn % mod;
    return limit;
}
//NTT
void NTT(Poly& x , bool type , int limit)
{
    x.set(limit - 1);
    for(int i = 0 ; i < limit ; i ++)
        if(i < _[i]) swap(x[i] , x[_[i]]);
    for(int mid = 1 ; mid < limit ; mid <<= 1)
        for(int j = 0 , i = limit/(2*mid); j < limit ; j += mid*2)
            for(int k = 0 ; k < mid ; k++)
            {
                int a = x[j + k] , b = 1ll * x[j + k + mid] * (type?w1[i*k]:w0[i*k]) % mod;
                x[j + k] = (a + b) % mod;
                x[j + k + mid] = (a - b + mod) % mod;                
            }
    if(type) return ;
    int64 inv = qpow(limit);
    for(int i = 0 ; i < limit ; i ++) x[i] = x[i] * inv % mod;
}
//乘法
Poly operator * (Poly a , Poly b)
{
    if(a.empty()) return a ; if(b.empty()) return b;
    int tot = a.degree()+b.degree();
    int limit = ntt_prepare(tot);
    NTT(a , 1 , limit) , NTT(b , 1 , limit);
    for(int i = 0 ; i < limit ; i ++) a[i] = 1ll*a[i]*b[i]%mod;
    NTT(a , 0 , limit) , a.set(tot);
    return a;
}
}
using namespace SYT_POLY;

const int N = 200020;
int fac[2*N] , ifac[2*N];
void C_init(int len)
{
    fac[0] = 1;
    for(int i = 1 ; i <= len ; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[len] = qpow(fac[len]);
    for(int i = len-1 ; ~i ; i --) ifac[i] = ifac[i + 1] * (i + 1ll) % mod;
}

int C(int x , int y) {
    if(y < 0 || y > x) return 0;
    return 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
inline int read() {
    int x = 0 ; char c = getchar(); bool f = 0;
    while(c < '0' || c > '9') f |= (c=='-') , c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + (c^48) , c = getchar();
    return f ? -x : x;
}

int n , m , ans;

Poly move(Poly a , int w) {
    if(w > a.degree()) {a.clear() ; return a;}
    for(int i = w ; i <= a.degree() ; ++i)
        a[i - w] = a[i];
    a.set(a.degree() - w);
    return a;
}

//EGF
Poly f[N];
Poly calc(int l , int r) {
    if(l == r) {
        Poly g = f[l];
        for(int i = 0 ; i <= g.degree() ; ++i)
            g[i] = 1LL * g[i] * ifac[i] % mod;
        return g;
    }
    int mid = (l + r) >> 1;
    return calc(l , mid) * calc(mid + 1 , r);
}
inline int sgn(int i) { return (i&1) ? mod - 1 : 1; }

int main() {
    freopen("always.in", "r", stdin);
    freopen("always1.out", "w", stdout);
    C_init(400010);
    n = read();
    
    for(int i = 1 ; i <= n ; ++i) {
        Poly A , B , &F = f[i];
        A.clear() , B.clear();
        int a = read(); m += a;
        A.set(a) , B.set(a);

        for(int j = 1 ; j <= a ; ++j)
            A[j] = 1LL * fac[j - 1] * C(a + j - 1 , a - j) % mod;
        if(i == 1) {
            for(int j = 1 ; j <= a ; ++j)
                A[j] = 1LL * A[j] * qpow(j) % mod;
        }
        for(int j = 0 ; j <= a ; ++j)
            B[a - j] = 1LL * sgn(j) * ifac[j] % mod;
        F = move(A * B , a);
        for(int j = 1 ; j <= a ; ++j)
            F[j] = 1LL * F[j] * ifac[j - 1] % mod;
        F[0] = 0;
    }
    Poly _2__n = calc(2 , n) , res;
    for ( int i = 1; i <= _2__n.degree(); ++ i ) printf("%d ", (_2__n[i] + mod) % mod); puts("");
    f[1] = move(f[1] , 1);
    for ( int i = 0; i <= f[1].degree(); ++ i ) printf("%lld ", (f[1][i] * ifac[i] % mod + mod) % mod); puts("");
    res = calc(1 , 1) * _2__n;
    for ( int i = 0; i <= res.degree(); ++ i ) printf("%lld ", (res[i] + mod) % mod); puts("");
    f[1] = move(f[1] , 1);
    res = res - calc(1 , 1) * _2__n;
    for ( int i = 0; i <= res.degree(); ++ i ) printf("%lld ", (res[i] + mod) % mod); puts("");
    for(int i = 1 ; i <= res.degree() ; ++i)
        ans = (ans + 1LL * res[i] * fac[i]) % mod;
    ans = 1LL * ans * m % mod;
    printf("%d\n" , ans);
    return 0;
}
