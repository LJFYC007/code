/***************************************************************
	File name: P4721.cpp
	Author: ljfcnyali
	Create time: 2020年01月10日 星期五 14时29分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int Mod = 998244353;

int r[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void NTT(int *a, int n, int opt)
{
    REP(i, 0, n - 1) 
    {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
        if ( i < r[i] ) swap(a[i], a[r[i]]);
    }
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( opt == -1 ) tmp = power(tmp, Mod - 2);
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j, sum = sum * tmp % Mod )
            {
                int x = a[i + j], y = a[i + j + Mid] * sum % Mod;
                a[i + j] = (x + y) % Mod; a[i + j + Mid] = (x - y) % Mod;
            }
        }
    }
    if ( opt == -1 ) 
    {
        int x = power(n, Mod - 2);
        REP(i, 0, n - 1) a[i] = a[i] * x % Mod;
    }
}

int f[maxn], g[maxn], a[maxn], b[maxn];

inline void Solve(int l, int r)
{
    if ( l == r ) { f[l] = (f[l] + (l == 0 ? 1 : 0)) % Mod; return ; }
    int Mid = l + r >> 1;
    Solve(l, Mid); 
    REP(i, 0, r - l + 1) a[i] = b[i] = 0;
    REP(i, l, Mid) a[i - l] = f[i]; 
    REP(i, 1, r - l) b[i - 1] = g[i];
    NTT(a, r - l + 1, 1); NTT(b, r - l + 1, 1);
    REP(i, 0, r - l) a[i] = a[i] * b[i] % Mod;
    NTT(a, r - l + 1, -1);
    REP(i, Mid + 1, r) f[i] = (f[i] + a[i - l - 1] + Mod) % Mod; 
    Solve(Mid + 1, r); 
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    scanf("%lld", &n);
    REP(i, 1, n - 1) scanf("%lld", &g[i]);
    m = 1; while ( m < n ) m <<= 1;
    Solve(0, m - 1);
    REP(i, 0, n - 1) printf("%lld ", f[i]); puts("");
    return 0;
}
