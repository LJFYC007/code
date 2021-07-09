/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年11月01日 星期五 14时54分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int Mod = 1e9 + 7;

int n, m, a[maxn][maxn], e[maxn][maxn], ans[maxn], X[maxn], Y[maxn];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline void DFS(int l, int r, int o, int suma, int sume)
{
    if ( l > r || !suma || sume > m ) return ;
    bool flag = false;
    REP(i, 1, r) if ( X[i] - 1 <= n - r ) { flag = true; break ; }
    if ( !flag ) return ;
    if ( r == n ) { ans[sume] = (ans[sume] + suma) % Mod; return ; }
    if ( o == 4 ) { DFS(l + 1, r, 0, suma, sume); return ; }
    int u = X[l] + dt[o][0], v = Y[l] + dt[o][1];
    if ( u < 1 || v < 1 || u > n || v > n || vis[u][v] ) { DFS(l, r, o + 1, suma, sume); return ; }
    vis[u][v] = true;
    DFS(l, r, o + 1, suma, sume);
    ++ r; X[r] = u; Y[r] = v;
    DFS(l, r, o + 1, suma * a[u][v] % Mod, sume + e[u][v]);
    vis[u][v] = false;
}

signed main()
{
    freopen("badwolf.in", "r", stdin);
    freopen("badwolf.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) REP(j, 1, n) { read(a[i][j]); read(e[i][j]); }
    REP(i, 1, n)
    {
        X[1] = i; Y[1] = 1; vis[i][1] = true; DFS(1, 1, 0, a[i][1], e[i][1]);
    }
    REP(i, 0, m) printf("%lld ", ans[i]); puts("");
    return 0;
}
