/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年07月23日 星期四 08时59分03秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;
 
const int maxn = 1010;
const int Mod = 1e9 + 7;
 
int n, k, q, fac[maxn], A[maxn];
vector<int> pre[maxn], suf[maxn], f[maxn], a;
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
 
vector<int> operator * (vector<int> a, vector<int> b)
{
    vector<int> c;
    int n = a.size(), m = b.size(), len = n + m - 1;
    c.resize(len); REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + a[i] * b[j]) % Mod;
    return c;
}
 
inline int sgn(int x) { return x & 1 ? -1 : 1; }
 
inline int F(int x)
{
    int ret = 0;
    REP(i, 0, k) ret = (ret + power(x, i) * a[i]) % Mod;
    return ret;
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &k, &q);
    fac[0] = 1; REP(i, 1, k) fac[i] = fac[i - 1] * i % Mod;
    REP(i, 0, k) scanf("%lld", &A[i]);
    a.resize(k + 1);
    if ( !k ) a[0] = A[0];
    else
    {
        REP(i, 0, k) { f[i].resize(2); f[i][0] = -i; f[i][1] = 1; }
        pre[0] = f[0]; REP(i, 1, k) pre[i] = pre[i - 1] * f[i];
        suf[k] = f[k]; for ( int i = k - 1; i >= 0; -- i ) suf[i] = suf[i + 1] * f[i];
        REP(i, 0, k)
        {
            int ret = fac[i] * fac[k - i] * sgn(k - i) % Mod;
            ret = power(ret, Mod - 2) * A[i] % Mod;
            vector<int> g; 
            if ( !i ) g = suf[i + 1];
            else if ( i < k ) g = pre[i - 1] * suf[i + 1];
            else g = pre[i - 1];
            REP(j, 0, k) a[j] = (a[j] + g[j] * ret) % Mod;
        }
    }
    int ans = 0;
    REP(i, 0, n) ans = (ans + F(i) * power(q, i)) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
