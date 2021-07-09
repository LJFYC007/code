#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long

const int maxn = 200010;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans;
int s[maxn][50], p[maxn], dep[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa, int t)
{
    s[u][++ t] = u;
    REP(i, 1, t) p[i] = s[u][i];
    int sum = 0, T = t; t = 0;
    for ( int i = T; i >= 1; -- i ) 
    {
        if ( i == T || __gcd(sum, a[p[i]]) != sum ) 
        {
            ++ t; s[u][t] = p[i];
            sum = __gcd(sum, a[p[i]]);
        }
    }
    sum = 0;
    REP(i, 1, t / 2) swap(s[u][i], s[u][t - i + 1]);
    for ( int i = t; i >= 1; -- i )
    {
        sum = __gcd(sum, a[s[u][i]]); ans = (ans + sum * (dep[s[u][i]] - dep[s[u][i - 1]])) % Mod;
    }
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        dep[v] = dep[u] + 1;
        for ( int j = t; j >= 1; -- j ) s[v][j] = s[u][j];
        DFS(v, u, t);
    }
}

signed main()
{
    scanf("%I64d", &n);
    REP(i, 1, n) scanf("%I64d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%I64d%I64d", &u, &v); add(u, v); add(v, u); }
    dep[1] = 1; DFS(1, 0, 0);
    printf("%I64d\n", ans);
    return 0;
}
