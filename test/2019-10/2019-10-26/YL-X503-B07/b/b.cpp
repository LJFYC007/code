/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年10月26日 星期六 09时36分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int maxn = 10010;
const int Mod = 998244353;

int n, f[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int a[2010][2010], p[maxn], tot;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 2, n) 
    {
        scanf("%lld", &f[i]);
        add(i, f[i]); add(f[i], i);
        if ( f[f[i]] ) { add(i, f[f[i]]), add(f[f[i]], i); }
    }
    a[1][1] = 1;
    REP(i, 2, n)
    {
        int num = 0;
        for ( int j = Begin[i]; j; j = Next[j] ) ++ num;
        num = power(num, Mod - 2);
        a[i][i] = a[i][n + 1] = 1;
        for ( int j = Begin[i]; j; j = Next[j] ) a[i][To[j]] = -num;
    }
    REP(i, 1, n)
    {
        int Max = i;
        REP(j, i + 1, n) if ( abs(a[j][i]) > abs(a[Max][i]) ) Max = j;
        REP(j, 1, n + 1) swap(a[i][j], a[Max][j]);
        tot = 0;
        REP(j, i + 1, n + 1) if ( a[i][j] ) p[++ tot] = j;
        int t = inv(a[i][i]);
        REP(j, 1, n) if ( j != i && a[j][i] != 0 ) REP(k, 1, tot)
        {
            int x = ((a[j][i] * a[i][p[k]] % Mod) * t) % Mod;
            a[j][p[k]] = (a[j][p[k]] - x + Mod) % Mod;
        }
    }
    REP(i, 1, n) printf("%lld\n", ((a[i][n + 1] * inv(a[i][i])) % Mod + Mod) % Mod);
    return 0;
}
