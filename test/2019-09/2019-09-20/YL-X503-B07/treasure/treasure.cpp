/***************************************************************
	File name: treasure.cpp
	Author: ljfcnyali
	Create time: 2019年09月20日 星期五 18时51分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;
const int Mod = 998244353;

int a[maxn], n, ans, Begin[maxn], Next[maxn], To[maxn], e, p[maxn], t[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = (r * a) % Mod; b >>= 1; a = (a * a) % Mod; }
    return r;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int sum, int x)
{
    ans = (ans + sum) % Mod;
    ++ x; sum = (sum * t[x]) % Mod;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v, sum, x);
    }
}

signed main()
{
    freopen("treasure.in", "r", stdin);
    freopen("treasure.out", "w", stdout);
    scanf("%lld", &n);
    p[1] = 1; REP(i, 2, n) p[i] = (p[i - 1] * i) % Mod, t[i] = power(i, Mod - 2);
    REP(i, 1, n) { scanf("%lld", &a[i]); if ( a[i] != -1 ) add(a[i], i); }
    REP(i, 1, n)
    {
        if ( a[i] != -1 ) continue ; 
        DFS(i, p[n], 1);
    }
    printf("%lld\n", (ans * power(p[n], Mod - 2)) % Mod);
    return 0;
}
