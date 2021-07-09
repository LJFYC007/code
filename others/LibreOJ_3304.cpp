/***************************************************************
	File name: LibreOJ_3304.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 10时31分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 40 * 40;
const int maxm = 2e5 + 10;
const int Mod = 998244353;

int n, m, phi[maxm], prime[maxm], tot, Begin[maxn], Next[maxn], To[maxn], e;
bool vis[maxm];
pii f[maxn][maxn];
struct node { int u, v, w; } Edge[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
pii operator + (pii a, pii b) { return pii((a.first + b.first) % Mod, (a.second + b.second) % Mod); }
pii operator - (pii a, pii b) { return pii((a.first - b.first) % Mod, (a.second - b.second) % Mod); }
pii operator * (pii a, pii b) { return pii(a.first * b.first % Mod, (a.second * b.first + a.first * b.second) % Mod); }
pii operator / (pii x, pii y) 
{ 
    int a = x.first, b = x.second, c = y.first, d = y.second;
    return pii(a * power(c, Mod - 2) % Mod, ((b * c - a * d) % Mod) * power(c * c % Mod, Mod - 2) % Mod);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    if ( vis[u] ) return ; vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
    }
}

inline int Gauss(int n)
{
    int ans = 1; -- n;

    REP(i, 1, n)
    {
        if ( f[i][i].first == 0 )
        {
            ans *= -1; int pos = i;
            REP(j, 1, n) if ( f[j][i].first != 0 ) { pos = j; break ; }
            REP(j, 1, n) swap(f[pos][j], f[i][j]);
        }
        REP(j, 1, n)
        {
            if ( j == i ) continue ;
            pii tmp = f[j][i] / f[i][i];
            REP(k, 1, n) f[j][k] = f[j][k] - f[i][k] * tmp;
        }
    }

    pii x = f[1][1];
    REP(i, 2, n) x = x * f[i][i];
    ans = ans * x.second % Mod;
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxm - 10;
    phi[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j] % Mod; break ; }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1) % Mod;
        }
    }

    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);

    int ans = 0;
    REP(i, 1, 152501)
    {
        e = 0; mem(Begin); REP(j, 1, n) vis[j] = false;
        REP(j, 1, m) if ( Edge[j].w % i == 0 )
        {
            add(Edge[j].u, Edge[j].v);
            add(Edge[j].v, Edge[j].u);
        }
        DFS(1);
        REP(j, 1, n) if ( !vis[j] ) goto Next ;

        REP(j, 1, n) REP(k, 1, n) f[j][k] = pii(0, 0);
        REP(j, 1, m) if ( Edge[j].w % i == 0 )
        {
            pii x = pii(1, Edge[j].w);
            int u = Edge[j].u, v = Edge[j].v, w = Edge[j].w;
            f[u][u] = f[u][u] + x; f[v][v] = f[v][v] + x;
            f[u][v] = f[u][v] - x; f[v][u] = f[v][u] - x;
        }
        ans = (ans + Gauss(n) * phi[i]) % Mod;
Next : ;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
