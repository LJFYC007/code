/***************************************************************
	File name: LibreOJ_3042.cpp
	Author: ljfcnyali
	Create time: 2020年07月22日 星期三 15时44分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define mp make_pair
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int Mod = 998244353;

int n, m, a[maxn], b[maxn], Edge[maxn][5], fac[maxn], inv[maxn];
struct data
{
    int f[3][3];
    bool operator < (const data &a) const { REP(i, 0, 2) REP(j, 0, 2) if ( f[i][j] != a.f[i][j] ) return f[i][j] < a.f[i][j]; return false; } 
} ;
struct node
{ 
    data f[2]; int t;
    bool operator < (const node &a) const { return mp(mp(f[0], f[1]), t) < mp(mp(a.f[0], a.f[1]), a.t); }
} g[maxn];
int f[110][maxn][410];
map<node, int> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }
inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

inline bool Check(node x) { return x.t >= 7 || x.f[1].f[0][0] >= 4; }

inline data max(data a, data b)
{
    REP(i, 0, 2) REP(j, 0, 2) a.f[i][j] = max(a.f[i][j], b.f[i][j]);
    return a;
}

inline data Trans(data x, int y)
{
    data X;
    REP(i, 0, 2) REP(j, 0, 2) X.f[i][j] = -1;
    REP(i, 0, 2) REP(j, 0, 2) REP(k, 0, 2)
    {
        if ( x.f[i][j] == -1 ) continue ;
        if ( y >= i + j + k ) X.f[j][k] = max(X.f[j][k], x.f[i][j] + k);
        if ( y >= i + j + k + 3 ) X.f[j][k] = max(X.f[j][k], x.f[i][j] + k + 1);
    }
    REP(i, 0, 2) REP(j, 0, 2) X.f[i][j] = min(X.f[i][j], 4ll);
    return X;
}

inline node Trans(node x, int y)
{
    node X; X.f[0] = Trans(x.f[0], y); X.f[1] = Trans(x.f[1], y); X.t = x.t;
    if ( y >= 2 ) { X.f[1] = max(X.f[1], Trans(x.f[0], y - 2)); X.t = min(x.t + 1, 7ll); }
    return X;
}

inline int DFS(node x)
{
    if ( Map.count(x) ) return Map[x]; 
    if ( Check(x) ) return 0;
    g[++ m] = x; Map[x] = m; int now = m; 
    REP(i, 0, 4) Edge[now][i] = DFS(Trans(x, i)); return now;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 0, 2) REP(j, 0, 2) g[1].f[0].f[i][j] = g[1].f[1].f[i][j] = -1;
    g[1].f[0].f[0][0] = 0; g[1].t = 0; DFS(g[1]);

    scanf("%lld", &n);
    REP(i, 1, 13) { int u, v; scanf("%lld%lld", &u, &v); ++ a[u]; }
    REP(i, 1, n) b[i] = b[i - 1] + a[i];
    
    f[0][1][0] = 1;
    REP(i, 1, n) REP(j, 1, m) REP(k, 0, 4 * n)
    {
        if ( !f[i - 1][j][k] ) continue ;
        REP(o, a[i], 4)
        {
            int t = Edge[j][o]; if ( !t ) continue ;
            int ret = C(k + o - b[i], o - a[i]) * A(4 - a[i], o - a[i]) % Mod;
            f[i][t][k + o] = (f[i][t][k + o] + f[i - 1][j][k] * ret) % Mod;
        }
    }
    int ans = 0;
    REP(i, 13, 4 * n) REP(j, 1, m) 
    {
        int ret = f[n][j][i];
        ret = ret * power(A(4 * n - 13, i - 13), Mod - 2) % Mod;
        ans = (ans + ret) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
